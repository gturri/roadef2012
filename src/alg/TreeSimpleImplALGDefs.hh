#ifndef TREESIMPLEIMPLALGDEFS_HH_
#define TREESIMPLEIMPLALGDEFS_HH_

#include "TreeSimpleImplALG.hh"
#include "tools/Log.hh"

template<class TreeSimpleImplALG>
TreeSimpleIteratorALG<TreeSimpleImplALG>
TreeSimpleIteratorALG<TreeSimpleImplALG>::father() const
{
    TreeSimpleIteratorALG<TreeSimpleImplALG> res_l = *this;

    res_l.pNode_m = path_m.back().first;
    res_l.path_m.pop_back();

    return res_l;
}


template <class NodeContent>
TreeSimpleImplALG<NodeContent>::TreeSimpleImplALG()
{
}

template <class NodeContent>
TreeSimpleImplALG<NodeContent>::~TreeSimpleImplALG()
{
}


template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator 
    TreeSimpleImplALG<NodeContent>::root()
{
    return iterator(&root_m);
}

template <class NodeContent>
void TreeSimpleImplALG<NodeContent>::deleteNode(iterator & it_p)
{
    if (it_p.pNode_m->second.size() != 0) {
        LOG(WTF) << "On essaie de deleter un node non vide!" << std::endl;
        return;
    }

    ChildrenList &cl_l = it_p.path_m.back().first->second;
    int idx_l = it_p.path_m.back().second;

    it_p.pNode_m->first.cleanup();
    cl_l.erase(cl_l.begin() + idx_l);
    // clear the iterator for bug visibility
    it_p.pNode_m = 0;
    it_p.path_m.clear();
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator
TreeSimpleImplALG<NodeContent>::addChildren(iterator &it_p,
                                            const NodeContent &content_p)
{
    it_p.pNode_m->second.push_back(Node(content_p,ChildrenList()));
    return iterator(it_p, it_p.pNode_m->second.size() - 1);
}

template <class NodeContent>
bool TreeSimpleImplALG<NodeContent>::hasChildren(const iterator & it_p)
{
	return (it_p.pNode_m->second.size() != 0);
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::ChildrenPool 
    TreeSimpleImplALG<NodeContent>::getChildren(const iterator & it_p)
{
    ChildrenPool pool_l;
    ChildrenList const &list_l = it_p.pNode_m->second;

    for (size_t i_l = 0; i_l < list_l.size(); ++i_l) {
        pool_l.push_back(iterator(it_p, i_l));
    }
    
    return pool_l;
}

#endif //TREESIMPLEIMPLALGDEFS_HH_
