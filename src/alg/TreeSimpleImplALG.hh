#ifndef TREESIMPLEIMPLALG_HH
#define TREESIMPLEIMPLALG_HH

#include <vector>
#include <list>

template<class NodeContent> class TreeSimpleImplALG;

template<class NodeContent>
struct TreeSimpleIteratorALG
{
    typedef TreeSimpleImplALG<NodeContent> * TreePointer;

    TreePointer pTree_m;
    int currentNode_m;

    TreeSimpleIteratorALG(int current_p,TreePointer pTree_p)
    : pTree_m(pTree_p),currentNode_m(current_p)
    {
    }
        
    NodeContent & operator*()
    {
        return pTree_m->getNodeContent(currentNode_m);
    }

    NodeContent const & operator*() const
    {
        return pTree_m->getNodeContent(currentNode_m);
    }
};

/** Classe servant d'exemple d'implementation d'un arbre
  * L'iterateur associe est tout aussi important que la
  * structure
  */


template <class NodeContent>
class TreeSimpleImplALG
{
    public:
        TreeSimpleImplALG();
        ~TreeSimpleImplALG();

        typedef TreeSimpleIteratorALG<NodeContent> iterator;
        typedef std::vector<iterator> ChildrenPool;

        iterator root();
        void deleteNode(iterator const &);
        iterator addChildren(iterator const &,NodeContent &);
        bool hasChildren(iterator const &);
        ChildrenPool getChildren(iterator const &);
 
        NodeContent & getNodeContent(int);
        bool hasChildren(int);

    private:
        typedef std::list<int> ChildrenList;
        typedef std::pair<NodeContent,ChildrenList> Node;
        typedef std::vector<Node> Nodes;

        Nodes nodes_m;
};

#endif
