#include "MonteCarloTreeSearchALG.hh"
#include "TreeALGDefs.hh"
#include "TreeSimpleImplALGDefs.hh"
#include "SpaceALG.hh"

#include <list>

typedef MonteCarloTreeSearchALG::Tree::ChildrenPool ChildrenPool;
typedef MonteCarloTreeSearchALG::Tree::iterator iterator; 

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    ( possibilite d'argument aussi)
  */
iterator chooseNextChildren(ChildrenPool const & children)
{
    return children.front();
}

void updatePath(std::list<iterator> & path_l, 
                std::list<SolutionALG *> const & solutions_l)
{
    
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
    return 0;
}

void MonteCarloTreeSearchALG::setpTree(Tree *)
{
}

MonteCarloTreeSearchALG::Tree * MonteCarloTreeSearchALG::getpTree() const
{
    return 0;
}

SpaceALG * MonteCarloTreeSearchALG::initNewSpace()
{
    return 0;
}

SpaceALG * MonteCarloTreeSearchALG::performDescent()
{
    SpaceALG * pSpace_l = initNewSpace();
    
    iterator current_l = pTree_m->getRootNode();

    bool hasCurrentNodeChildren = pTree_m->hasChildren(current_l);
    std::list<iterator> pathToLeaf_l;
    
    //On descent jusqu'une feuille
    while (hasCurrentNodeChildren)
    {
        // on recupere les fils du noeud courant
        ChildrenPool children_l = pTree_m->getChildren(current_l);
        // on choisi le noeud suivant grace a la formule magique
        iterator nextChild_l = chooseNextChildren(children_l);
        // On retient le noeud par lequel on est passe
        pathToLeaf_l.push_back(current_l);
        // On avance au noeud suivant
        current_l = nextChild_l;
        // On restreint l'espace de solution
        pSpace_l->addDecision((*current_l).pDecision_m);
        // on regarde si l'on est arrive sur une feuille
        hasCurrentNodeChildren = pTree_m->hasChildren(current_l);
    }

    // Maintenant qu'on est sur une feuille on va brancher selon l'espace des solutions
    typedef SpaceALG::DecisionsPool DecisionsPool;
    DecisionsPool decisions_l = pSpace_l->generateDecisions();

    // On va retenir les solutions que l'on a trouver
    std::list<SolutionALG *> results_l;
    // Pour chaque decision de branchement, on fait une simulation et une recherche locale
    for(DecisionsPool::iterator decisionIt_l = decisions_l.begin(); decisionIt_l != decisions_l.end(); ++decisionIt_l )
    {
        // on ajoute le noeud a l'arbre
        NodeContentALG content_l(*decisionIt_l);
        pTree_m->addChildren(current_l, content_l);
        SpaceALG * pChildSpace_l = pSpace_l->clone();
        pChildSpace_l->addDecision(*decisionIt_l);
        SolutionALG * pSolution_l = pChildSpace_l->buildSolution();
        results_l.push_back(pSolution_l);
        delete pChildSpace_l;
    }

    // On remonte l'information
    updatePath(pathToLeaf_l,results_l);

    return pSpace_l;
}
