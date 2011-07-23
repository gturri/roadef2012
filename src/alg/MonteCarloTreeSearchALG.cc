#include "MonteCarloTreeSearchALG.hh"
#include "TreeALG.hh"
#include "SpaceALG.hh"

#include <list>

typedef TreeALG::ChildrenInfoPool ChildrenPool;

/** Externalisation du choix dans le cc pour rendre le code lisible
    Si il y a besoin d'element de la classe, on peut toujours la faire
    remonter en prive, mais ca sera le bordel au niveau inclusion
    ( possibilite d'argument aussi)
  */
int chooseNextChildren(ChildrenPool const & children)
{
    return 0;
}

void updatePath(std::list<NodeContentALG *> & path_l, std::list<SolutionALG *> const & solutions_l)
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

void MonteCarloTreeSearchALG::setpTree(TreeALG *)
{
}

TreeALG * MonteCarloTreeSearchALG::getpTree() const
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

    pTree_m->setCurrentNodeToRoot();

    bool hasCurrentNodeChildren = pTree_m->hasCurrentNodeChildren();
    std::list<NodeContentALG *> pathToLeaf_l;
    
    //On descent jusqu'une feuille
    while (hasCurrentNodeChildren)
    {
    	// on recupere les fils du noeud courant
    	ChildrenPool children_l = pTree_m->getChildrenOfCurrentNode();
    	// on choisi le noeud suivant grace a la formule magique
    	int nextChild_l = chooseNextChildren(children_l);
    	// On avance au noeud suivant
    	NodeContentALG * pContent_l = pTree_m->setCurrentNodeToChild(nextChild_l);
    	// On retient le noeud par lequel on est passe
    	pathToLeaf_l.push_back(pContent_l);
    	// On restreint l'espace de solution
    	pSpace_l->addDecision(pContent_l->pDecision_m);
    	// on regarde si l'on est arrive sur une feuille
    	hasCurrentNodeChildren = pTree_m->hasCurrentNodeChildren();
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
    	pTree_m->addChildrenToCurrentNode(*decisionIt_l);
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
