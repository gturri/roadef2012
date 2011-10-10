#ifndef TREESIMPLEIMPLALGDEFS_HH_
#define TREESIMPLEIMPLALGDEFS_HH_

#include "TreeSimpleImplALG.hh"

template <class NodeContent>
TreeSimpleImplALG<NodeContent>::TreeSimpleImplALG()
{
    nodes_m.push_back(Node());
}

template <class NodeContent>
TreeSimpleImplALG<NodeContent>::~TreeSimpleImplALG()
{
}


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
    size_t nextId_l = nodes_m.size();
    nodes_m.at(it_p.currentNode_m).second.push_back(nextId_l);
    nodes_m.push_back(Node(NodeContent(content_p),ChildrenList()));
    return iterator(nextId_l,this);
}

template <class NodeContent>
bool TreeSimpleImplALG<NodeContent>::hasChildren(iterator const & it_p)
{
	return (nodes_m.at(it_p.currentNode_m).second.size() != 0);
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::ChildrenPool 
    TreeSimpleImplALG<NodeContent>::getChildren(iterator const & it_p)
{
    ChildrenPool pool_l;
    ChildrenList const & list_l = nodes_m.at(it_p.currentNode_m).second;
    for (ChildrenList::const_iterator it_l = list_l.begin();
                                      it_l != list_l.end();
                                      ++it_l)
    {
        pool_l.push_back(iterator(*it_l,this));
    }
    
    return pool_l;
}


template <class NodeContent>
NodeContent & TreeSimpleImplALG<NodeContent>::getNodeContent(int node_p)
{
    // test + throw tout ca
    return nodes_m.at(node_p).first;
}


#endif //TREESIMPLEIMPLALGDEFS_HH_
