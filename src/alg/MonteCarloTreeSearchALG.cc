#include "MonteCarloTreeSearchALG.hh"
#include "ConstraintSystemALG.hh"
#include "EvaluationSystemALG.hh"
#include "TreeALGDefs.hh"
#include "TreeSimpleImplALGDefs.hh"
#include "SolutionALG.hh"
#include "SpaceALG.hh"

#include <list>
#include "tools/Log.hh"

typedef MonteCarloTreeSearchALG::Tree::ChildrenPool ChildrenPool;
typedef MonteCarloTreeSearchALG::Tree::iterator iterator; 

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    ( possibilite d'argument aussi)
  */
iterator chooseNextChildren(ChildrenPool const & children_p)
{
    iterator childrenToExplore_l(children_p.front());
    double minValue_l = 0.0;
    for (ChildrenPool::const_iterator it_l = children_p.begin();
                                      it_l != children_p.end(); 
                                      ++it_l)
    {
        MonteCarloTreeSearchALG::Tree::iterator const & treeIt_l = *it_l;
        NodeContentALG const & content_l = *treeIt_l;
        // inserer ici la formule qui va bien
        double value_l = content_l.sumOfEvaluations_m;
        value_l /= content_l.numberOfSimulations_m;
        if (value_l > minValue_l)
        {
            minValue_l = value_l;
            childrenToExplore_l = *it_l;
        }
    }
    return childrenToExplore_l;
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
    }
    
    for (std::list<iterator>::iterator it_l = path_p.begin();
                                       it_l != path_p.end();
                                       ++it_l)
    {
        iterator & treeIt_l = *it_l;
        NodeContentALG & content_l = *treeIt_l;
        content_l.sumOfEvaluations_m += sum_l;
        content_l.numberOfSimulations_m += evaluations_l;
    }
}

MonteCarloTreeSearchALG::MonteCarloTreeSearchALG()
: pTree_m(0)
{
}

MonteCarloTreeSearchALG::~MonteCarloTreeSearchALG()
{
}

SolutionALG * MonteCarloTreeSearchALG::search()
{
    LOG(DEBUG) << "Recherche arborescente de Monte Carlo" << std::endl;
    
    double bestEval_l = 0.0;
    SolutionALG * pBestOne_l = 0;
    for (int i_l = 0; i_l < 10; ++i_l)
    {
        SpaceALG * pSpace_l = performDescent();
        SolutionALG * pSolution_l = pSpace_l->buildSolution();
        double value_l = pSolution_l->evaluate();
        if (value_l > bestEval_l )
        {
            bestEval_l = value_l;
            delete pBestOne_l;
            pBestOne_l = pSolution_l;
        }
        else
        {
            delete pSolution_l;
        }
        delete pSpace_l;
    }
    return pBestOne_l;
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

    bool hasCurrentNodeChildren = pTree_m->hasChildren(current_l);
    std::list<iterator> pathToLeaf_l;
    
     LOG(DEBUG) << "Descente" << std::endl;
    //On descent jusqu'une feuille
    while (hasCurrentNodeChildren)
    {
         LOG(DEBUG) << "on recupere les fils du noeud courant" << std::endl;
        // on recupere les fils du noeud courant
        ChildrenPool children_l = pTree_m->getChildren(current_l);
        LOG(DEBUG) << "on choisi le noeud suivant grace a la formule magique" << std::endl;
        // on choisi le noeud suivant grace a la formule magique
        iterator nextChild_l = chooseNextChildren(children_l);
        LOG(DEBUG) << "On retient le noeud par lequel on est passe" << std::endl;
        // On retient le noeud par lequel on est passe
        pathToLeaf_l.push_back(current_l);
        LOG(DEBUG) << "On avance au noeud suivant" << std::endl;
        // On avance au noeud suivant
        current_l = nextChild_l;
        LOG(DEBUG) << "On restreint l'espace de solution" << std::endl;
        // On restreint l'espace de solution
        pSpace_l->addDecision((*current_l).pDecision_m);
        LOG(DEBUG) << "on regarde si l'on est arrive sur une feuille" << std::endl;
        // on regarde si l'on est arrive sur une feuille
        hasCurrentNodeChildren = pTree_m->hasChildren(current_l);
    }
    
     LOG(DEBUG) << "Maintenant qu'on est sur une feuille on va brancher" << std::endl;
    // Maintenant qu'on est sur une feuille on va brancher selon l'espace des solutions
    typedef SpaceALG::DecisionsPool DecisionsPool;
    DecisionsPool decisions_l = pSpace_l->generateDecisions();

    LOG(DEBUG) << "On va retenir les solutions que l'on a trouver" << std::endl;
    // On va retenir les solutions que l'on a trouver
    std::list<SolutionALG *> results_l;
    // Pour chaque decision de branchement, on fait une simulation et une recherche locale
    for(DecisionsPool::iterator decisionIt_l = decisions_l.begin(); decisionIt_l != decisions_l.end(); ++decisionIt_l )
    {
         LOG(DEBUG) << "on ajoute le noeud a l'arbre" << std::endl;       
        // on ajoute le noeud a l'arbre
        NodeContentALG content_l(*decisionIt_l);
         LOG(DEBUG) << "on clone l'espace courant" << std::endl;       
        // on clone l'espace courant
        SpaceALG * pChildSpace_l = pSpace_l->clone();
         LOG(DEBUG) << "on ajoute les decisions" << std::endl;       
        // on ajoute les decisions
        pChildSpace_l->addDecision(*decisionIt_l);
         LOG(DEBUG) << "est-ce une solution?" << std::endl;       
        // est-ce une solution
        if (!pChildSpace_l->isSolution())
        {
            pTree_m->addChildren(current_l, content_l);
            // traiter la solution
        }
         LOG(DEBUG) << "on construit la solution en appelant monte carlo" << std::endl;       
        // on construit la solution en appelant monte carlo
        SolutionALG * pSolution_l = pChildSpace_l->buildSolution();
         LOG(DEBUG) << "on ajoute la solution" << std::endl;       
        // on ajoute la solution
        results_l.push_back(pSolution_l);        
        delete pChildSpace_l;
    }

     LOG(DEBUG) << "On remonte l'information" << std::endl;
    // On remonte l'information
    updatePath(pathToLeaf_l,results_l);

    return pSpace_l;
}

