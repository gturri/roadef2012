#include "MonteCarloTreeSearchALG.hh"
#include "ConstraintSystemALG.hh"
#include "EvaluationSystemALG.hh"
#include "TreeALGDefs.hh"
#include "TreeSimpleImplALGDefs.hh"
#include "SolutionALG.hh"
#include "SpaceALG.hh"

#include <list>
#include <sstream>
#include "tools/Log.hh"

typedef MonteCarloTreeSearchALG::Tree::ChildrenPool ChildrenPool;
typedef MonteCarloTreeSearchALG::Tree::iterator iterator; 

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    ( possibilite d'argument aussi)
*/

double uct(const NodeContentALG &node_p)
{
    // pour le moment, on fait juste le moins explore
    if (node_p.numberOfSimulations_m == 0)
        return 2.;

    return 1. / node_p.numberOfSimulations_m;
}

iterator chooseNextChildren(ChildrenPool const & children_p)
{
    ChildrenPool::const_iterator it_l = children_p.begin();
    iterator childrenToExplore_l(*it_l);
    std::stringstream dump_l;
    double maxValue_l = uct(*childrenToExplore_l);

    dump_l << maxValue_l << "+";

    for (++it_l; it_l != children_p.end(); ++it_l)
    {
        // inserer ici la formule qui va bien
        double value_l = uct(**it_l);
        dump_l << " " << value_l;
        if (value_l > maxValue_l)
        {
            maxValue_l = value_l;
            childrenToExplore_l = *it_l;
            dump_l << "+";
        }
    }
    LOG(DEBUG) << "chooseNextChild: " << dump_l.str() << std::endl;
    return childrenToExplore_l;
}

void updateNode(iterator &it_p, double sum_p, int nb_p)
{
    NodeContentALG & content_l = *it_p;
    content_l.sumOfEvaluations_m += sum_p;
    content_l.numberOfSimulations_m += nb_p;
}

void updatePath(std::list<iterator> & path_p, 
                std::list<SolutionALG *> const & solutions_p)
{
    typedef std::list<SolutionALG *> Solutions;
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
    
    for (std::list<iterator>::iterator it_l = path_p.begin();
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
    delete pTree_m;
}

SolutionALG * MonteCarloTreeSearchALG::search()
{
    LOG(DEBUG) << "Recherche arborescente de Monte Carlo" << std::endl;
    
    for (int i_l = 0; i_l < 10; ++i_l)
    {
        SpaceALG * pSpace_l = performDescent();
        LOG(DEBUG) << std::endl << pTree_m->toString();
    }
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
    std::list<iterator> pathToLeaf_l;
    
    pathToLeaf_l.push_back(current_l);
    LOG(DEBUG) << "Descente" << std::endl;

    //On descent jusqu'une feuille
    while (pTree_m->hasChildren(current_l))
    {
        // on recupere les fils du noeud courant
        ChildrenPool children_l = pTree_m->getChildren(current_l);
        // on choisi le noeud suivant grace a la formule magique
        iterator nextChild_l = chooseNextChildren(children_l);
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
    std::list<SolutionALG *> results_l;
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
