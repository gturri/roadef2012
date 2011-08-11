#ifndef TREESIMPLEIMPLALGDEFS_HH_
#define TREESIMPLEIMPLALGDEFS_HH_

#include "TreeSimpleImplALG.hh"

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator 
    TreeSimpleImplALG<NodeContent>::root()
{
    return iterator(0,this);
}


template <class NodeContent>
void TreeSimpleImplALG<NodeContent>::deleteNode(iterator const & it_p)
{
    
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator
    TreeSimpleImplALG<NodeContent>::addChildren( iterator const & it_p,
                                                  NodeContent & content_p)
{
    return it_p;
}

template <class NodeContent>
bool TreeSimpleImplALG<NodeContent>::hasChildren(iterator const & it_p)
{
    return true;
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::ChildrenPool 
    TreeSimpleImplALG<NodeContent>::getChildren(iterator const & it_p)
{
    return ChildrenPool();
}


template <class NodeContent>
NodeContent & TreeSimpleImplALG<NodeContent>::getNodeContent(int node_p)
{
    // test + throw tout ca
    return nodes_m[node_p].first;
}


#endif //TREESIMPLEIMPLALGDEFS_HH_
