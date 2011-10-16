#ifndef TREESIMPLEIMPLALG_HH
#define TREESIMPLEIMPLALG_HH

#include <vector>
#include <list>

template<class TreeSimpleImplALG>
struct TreeSimpleIteratorALG
{
    typedef typename TreeSimpleImplALG::NodeContent NodeContent;
    typedef typename TreeSimpleImplALG::Node Node;

    TreeSimpleIteratorALG(Node *pN_p) :
        pNode_m(pN_p)
    {
    }
    TreeSimpleIteratorALG(const TreeSimpleIteratorALG &it_p, size_t idx_p) :
        pNode_m(0),
        path_m(it_p.path_m)
    {
        path_m.push_back(std::make_pair(it_p.pNode_m, idx_p));
        pNode_m = &it_p.pNode_m->second[idx_p];
    }

    TreeSimpleIteratorALG father() const;
    bool isRoot() const {return path_m.size() == 0;}
    NodeContent &operator*() {return pNode_m->first;}
    const NodeContent &operator*() const {return pNode_m->first;}
    NodeContent &operator->() {return pNode_m->first;}
    const NodeContent &operator->() const {return pNode_m->first;}

    // should be protected
    typedef std::pair<Node*,size_t> Vertex;
    typedef std::vector<Vertex> Path;

    Node *pNode_m;
    Path path_m;
};

/** Classe servant d'exemple d'implementation d'un arbre
  * L'iterateur associe est tout aussi important que la
  * structure
  */


template <class T>
class TreeSimpleImplALG
{
public:
    typedef T NodeContent;
    typedef TreeSimpleIteratorALG<TreeSimpleImplALG> iterator;
    typedef std::vector<iterator> ChildrenPool;

    TreeSimpleImplALG();
    ~TreeSimpleImplALG();

    iterator root();
    void deleteNode(iterator &);
    iterator addChildren(iterator &, const NodeContent &);
    bool hasChildren(iterator const &);
    ChildrenPool getChildren(iterator const &);
    
    // should be potected
    struct Node
    {
        typedef std::vector<Node> ChildrenList;
        Node() {}
        Node(const NodeContent &nc_p, const ChildrenList &v_p) :
            first(nc_p), second(v_p)
        {}
        NodeContent first;
        ChildrenList second;
    };
    typedef typename Node::ChildrenList ChildrenList;    
protected:
    Node root_m;
};

#endif
