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
#include "tools/Log.hh"

typedef MonteCarloTreeSearchALG::Tree::ChildrenPool ChildrenPool;
typedef MonteCarloTreeSearchALG::Tree::iterator iterator; 

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    ( possibilite d'argument aussi)
*/

// voir http://arxiv.org/abs/cs/0703062v1 pour pleins de formules cools
double uct(const NodeContentALG &node_p, const std::vector<iterator> &path_p)
{
    if (node_p.numberOfSimulations_m == 0)
        return std::numeric_limits<double>::infinity();

    // number of eval of the parent
    double p_l = (**path_p.rbegin()).numberOfSimulations_m;
    double ni_l = node_p.numberOfSimulations_m;
    double mean_l = node_p.sumOfEvaluations_m / ni_l;
    double ci_l = sqrt(2. * log(p_l) / ni_l);

    return mean_l + ci_l;
}

iterator
chooseNextChildren(ChildrenPool const & children_p,
                   const std::vector<iterator> &path_p)
{
    ChildrenPool::const_iterator it_l = children_p.begin();
    iterator childrenToExplore_l(*it_l);
    std::stringstream dump_l;
    double maxValue_l = uct(**it_l, path_p);

    for (++it_l; it_l != children_p.end(); ++it_l) {
        double value_l = uct(**it_l, path_p);
        if (value_l > maxValue_l) {
            maxValue_l = value_l;
            childrenToExplore_l = *it_l;
        }
    }
    return childrenToExplore_l;
}

void updateNode(iterator &it_p, double sum_p, int nb_p)
{
    NodeContentALG & content_l = *it_p;
    content_l.sumOfEvaluations_m += sum_p;
    content_l.numberOfSimulations_m += nb_p;
}

void
updatePath(std::vector<iterator> & path_p,
           std::vector<SolutionALG *> const & solutions_p)
{
    typedef std::vector<SolutionALG *> Solutions;
    double sum_l = 0.0;
    int evaluations_l = 0;
    
    // Calcul de l'impact des evaluations sur l'arbre, certainement faux
    for (Solutions::const_iterator it_l = solutions_p.begin();
         it_l != solutions_p.end();
         ++it_l)
    {
        SolutionALG * pSolution_l = *it_l;
        sum_l += pSolution_l->evaluate();
        evaluations_l += 1;
        delete pSolution_l;
    }
    
    for (std::vector<iterator>::iterator it_l = path_p.begin();
         it_l != path_p.end();
         ++it_l)
    {
        updateNode(*it_l, sum_l, evaluations_l);
    }
}

MonteCarloTreeSearchALG::MonteCarloTreeSearchALG() :
    pTree_m(0)
{
}

MonteCarloTreeSearchALG::~MonteCarloTreeSearchALG()
{
}

SolutionALG * MonteCarloTreeSearchALG::search()
{
    LOG(INFO) << "Lancement de MCTS" << std::endl;
    
    for (int i_l = 0; i_l < 100000; ++i_l)
    {
        SpaceALG * pSpace_l = performDescent();
    }
    LOG(INFO) << std::endl << pTree_m->toString(2);
    return pInitialSpace_m->buildSolution();
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
    SpaceALG * pSpace_l = pInitialSpace_m->clone();
    return pSpace_l;
}

SpaceALG * MonteCarloTreeSearchALG::performDescent()
{
    SpaceALG * pSpace_l = initNewSpace();
    iterator current_l = pTree_m->getRootNode();
    std::vector<iterator> pathToLeaf_l;
    
    pathToLeaf_l.push_back(current_l);
    LOG(DEBUG) << "Descente" << std::endl;

    //On descent jusqu'une feuille
    while (pTree_m->hasChildren(current_l))
    {
        // on recupere les fils du noeud courant
        ChildrenPool children_l = pTree_m->getChildren(current_l);
        // on choisi le noeud suivant grace a la formule magique
        iterator nextChild_l = chooseNextChildren(children_l, pathToLeaf_l);
        // On avance au noeud suivant
        current_l = nextChild_l;
        // On retient le noeud par lequel on est passe
        pathToLeaf_l.push_back(current_l);
        // On restreint l'espace de solution
        pSpace_l->addDecision((*current_l).pDecision_m);
    }
    
    // Maintenant qu'on est sur une feuille on va brancher selon l'espace des
    // solutions
    typedef SpaceALG::DecisionsPool DecisionsPool;
    DecisionsPool decisions_l = pSpace_l->generateDecisions();

    // On va retenir les solutions que l'on a trouver
    std::vector<SolutionALG *> results_l;
    // Pour chaque decision de branchement, on fait une simulation et une
    // recherche locale
    for (DecisionsPool::iterator decisionIt_l = decisions_l.begin();
         decisionIt_l != decisions_l.end(); ++decisionIt_l)
    {
        // on ajoute le noeud a l'arbre
        NodeContentALG content_l(*decisionIt_l);
        // on clone l'espace courant
        SpaceALG * pChildSpace_l = pSpace_l->clone();
        // on ajoute les decisions
        pChildSpace_l->addDecision(*decisionIt_l);
        // on ajoute le nouveau noeud
        iterator newNode_l = pTree_m->addChildren(current_l, content_l);
        // traiter la solution
        // on construit la solution en appelant monte carlo
        SolutionALG * pSolution_l = pChildSpace_l->buildSolution();
        // on ajoute la solution
        updateNode(newNode_l, pSolution_l->evaluate(), 1);
        results_l.push_back(pSolution_l);        
        delete pChildSpace_l;
        if (!pChildSpace_l->isSolution())
        {
            // TODO delete le noeud, et si pas de fils, le papa, etc et
            // updater le chelin restant
        }
    }

    // On remonte l'information
    updatePath(pathToLeaf_l,results_l);

    return pSpace_l;
}
