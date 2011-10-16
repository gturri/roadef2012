#ifndef TREESIMPLEIMPLALG_HH
#define TREESIMPLEIMPLALG_HH

#include <assert.h>
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
        assert(idx_p < it_p.pNode_m->children_m.size());
        path_m.push_back(std::make_pair(it_p.pNode_m, idx_p));
        pNode_m = &(it_p.pNode_m->children_m[idx_p]);
    }

    TreeSimpleIteratorALG father() const;
    bool isRoot() const {return path_m.size() == 0;}
    NodeContent &operator*() {return pNode_m->content_m;}
    const NodeContent &operator*() const {return pNode_m->content_m;}
    NodeContent *operator->() {return &pNode_m->content_m;}
    const NodeContent *operator->() const {return &pNode_m->content_m;}

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
            content_m(nc_p), children_m(v_p)
        {}
        NodeContent content_m;
        ChildrenList children_m;
    };
    typedef typename Node::ChildrenList ChildrenList;    
protected:
    Node root_m;
};

#endif
