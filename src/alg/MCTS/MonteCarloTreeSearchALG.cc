#include "MonteCarloTreeSearchALG.hh"
#include "ConstraintSystemALG.hh"
#include "EvaluationSystemALG.hh"
#include "TreeALGDefs.hh"
#include "TreeSimpleImplALGDefs.hh"
#include "SolutionALG.hh"
#include "SpaceALG.hh"

#include <list>
#include <sstream>
#include <limits>
#include <cmath>
#include <algorithm>
#include "tools/Log.hh"

#include <boost/tuple/tuple.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

using boost::ref;
using boost::bind;
using boost::thread_group;
using boost::tuple;

typedef MonteCarloTreeSearchALG::Tree::ChildrenPool ChildrenPool;
typedef MonteCarloTreeSearchALG::Tree::iterator iterator; 

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    (possibilite d'argument aussi)
*/

// voir http://arxiv.org/abs/cs/0703062v1 pour pleins de formules cools
double uct(const iterator &it_p)
{
    if (it_p->nbSimu_m == 0 || it_p.isRoot())
        return std::numeric_limits<double>::infinity();

    double p_l = it_p.father()->nbSimu_m;
    double ni_l = it_p->nbSimu_m;
    double mean_l = it_p->sumEval_m / ni_l;
    double ci_l = sqrt(2. * log(p_l) / ni_l);

    return mean_l + 0.1 * ci_l;
}

iterator
chooseNextChildren(MonteCarloTreeSearchALG::Tree *pTree_p, const iterator &it_p)
{
    ChildrenPool children_l = pTree_p->children(it_p);
    ChildrenPool::const_iterator itPool_l = children_l.begin();
    iterator res_l = *itPool_l;
    double maxValue_l = uct(*itPool_l);

    for (++itPool_l; itPool_l != children_l.end(); ++itPool_l) {
        double value_l = uct(*itPool_l);
        if (value_l > maxValue_l) {
            maxValue_l = value_l;
            res_l = *itPool_l;
        }
    }
    return res_l;
}

void updateNode(iterator &it_p, int nb_p, double sum_p)
{
    it_p->nbSimu_m += nb_p;
    it_p->sumEval_m += sum_p;
    // for rounding errors
    it_p->sumEval_m = std::max<float>(0, it_p->sumEval_m);
}

void updatePath(iterator it_p, int nb_p, double sum_p)
{
    while (! it_p.isRoot()) {
        updateNode(it_p, nb_p, sum_p);
        it_p = it_p.father();
    }
    updateNode(it_p, nb_p, sum_p);
}

MonteCarloTreeSearchALG::MonteCarloTreeSearchALG() :
    pTree_m(0)
{
}

MonteCarloTreeSearchALG::~MonteCarloTreeSearchALG()
{
}

bool isPowerOf10(int i_p)
{
    if (i_p <= 0)
        return true;

    int log_l = log10(i_p);
    return i_p % ((int) pow(10., log_l)) == 0;
}

void MonteCarloTreeSearchALG::search()
{
    LOG(INFO) << "Lancement de MCTS" << std::endl;
    int i_l = 0, nbSimu_l = 0;
    
    do {
        ++i_l;
        nbSimu_l += performDescent();
        if (isPowerOf10(i_l)) {
            LOG(INFO) << "nb iter = " << i_l << ", nbSimu = " << nbSimu_l
                      << ", tree = " << pTree_m->toString(2) << std::endl;;
        }
    } while (pTree_m->hasChildren(pTree_m->root()));

    LOG(INFO) << "End MCTS: nb iter = " << i_l << ", nbSimu = " << nbSimu_l
              << std::endl;
}

void MonteCarloTreeSearchALG::setpTree(Tree * pTree_p)
{
    pTree_m = pTree_p;
}

MonteCarloTreeSearchALG::Tree * MonteCarloTreeSearchALG::getpTree() const
{
    return pTree_m;
}

void MonteCarloTreeSearchALG::setpInitialSpace(SpaceALG * pSpace_p)
{
    pInitialSpace_m = pSpace_p;
}

SpaceALG * MonteCarloTreeSearchALG::initNewSpace()
{
    return pInitialSpace_m->clone();
}

void callable_evaluate(SpaceALG * pSpace_p,double & d_p)
{
    d_p = pSpace_p->evaluate();
}

int MonteCarloTreeSearchALG::performDescent()
{
    SpaceALG * pSpace_l = initNewSpace();
    iterator current_l = pTree_m->root();

    //On descent jusqu'une feuille
    while (pTree_m->hasChildren(current_l)) {
        current_l = chooseNextChildren(pTree_m, current_l);
        pSpace_l->addDecision(current_l->pDecision_m);
    }
    
    // Maintenant qu'on est sur une feuille on va brancher selon l'espace des
    // solutions
    typedef SpaceALG::DecisionsPool DecisionsPool;
    DecisionsPool decisions_l = pSpace_l->generateDecisions();

    // On va retenir les évaluations à faire remonter
    int nbSimu_l = 0;
    double sumEval_l = 0;

    typedef tuple<SpaceALG *,DecisionALG *,double> Eval;
    typedef std::list<Eval> EvalPool;
    EvalPool pool_l;

    boost::thread_group group_l;

    for (DecisionsPool::iterator it_l = decisions_l.begin();
         it_l != decisions_l.end(); ++it_l) {
        SpaceALG * pChildSpace_l = pSpace_l->clone();
        pChildSpace_l->addDecision(*it_l);
        pool_l.push_back(Eval(pChildSpace_l,*it_l,0.0));
        group_l.create_thread( bind(callable_evaluate,
                                    ref(pool_l.back().get<0>()),
                                    ref(pool_l.back().get<2>())) );
    }

    group_l.join_all();

    for(EvalPool::iterator it_l = pool_l.begin(); it_l != pool_l.end(); ++it_l)
    {
        SpaceALG * pChildSpace_l = it_l->get<0>();
        double eval_l = it_l->get<2>();

        if (pChildSpace_l->isSolution()) {
            // on delete la decision car on ne l'ajoute pas à l'arbre
            delete it_l->get<1>();
        } else {
            // si c'est pas une solution, on l'ajoute à l'arbre
            NodeContentALG newNC_l(it_l->get<1>());
            iterator newNode_l = pTree_m->addChildren(current_l, newNC_l);

            // on met à jour les évaluations
            updateNode(newNode_l, 1, eval_l);
            ++nbSimu_l;
            sumEval_l += eval_l;
        }
        delete pChildSpace_l;
    }

    if (nbSimu_l == 0) {
        // pas de fils généré, on efface le noeud et ses pères vides en cascade
        while (! pTree_m->hasChildren(current_l) && ! current_l.isRoot()) {
            iterator father_l = current_l.father();
            // on sauve les données à effacer
            nbSimu_l = - current_l->nbSimu_m;
            sumEval_l = - current_l->sumEval_m;
            // on delete
            pTree_m->deleteNode(current_l);
            current_l = father_l;
        }
    }

    // On remonte l'information
    updatePath(current_l, nbSimu_l, sumEval_l);

    delete pSpace_l;
    return std::max(0, nbSimu_l);
}
