#ifndef TREEALG_HH
#define TREEALG_HH

#include <map>
#include <vector>
#include <list>

/** Structure contenant l'information utile du noeud d'un point de vue
    recherche de solution. Quelque soit la structure de l'arbre, on en
    aura toujours besoin.
  */

class DecisionALG;

struct NodeContentALG
{
    int numberOfSimulations_m;
    double sumOfEvaluations_m;
    DecisionALG * pDecision_m;
};

/** Classe pouvant servir a terme d'interface pour l'arbre. L'arbre gere
    lui meme le noeud

  */

class TreeALG
{
    public:
        TreeALG();
        ~TreeALG();

        typedef std::vector<NodeContentALG *> ChildrenInfoPool;

        void setCurrentNodeToRoot();
        ChildrenInfoPool getChildrenOfCurrentNode();
        NodeContentALG * setCurrentNodeToChild(int);

        bool hasCurrentNodeChildren();
        NodeContentALG * getCurrentNodeInformation();
        void addChildrenToCurrentNode(DecisionALG *);

    private:
        typedef std::list<int> ChildrenList;
        typedef std::pair<NodeContentALG,ChildrenList> Node;
        typedef std::vector<Node> Nodes;

        Nodes nodes_m;
        int currentNode_m;
};

#endif
