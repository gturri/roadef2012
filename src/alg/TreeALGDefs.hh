#ifndef TREEALGDEFS_HH_
#define TREEALGDEFS_HH_

#include "TreeALG.hh"

template<typename TreeImpl>
TreeALG<TreeImpl>::TreeALG()
{
}

template<typename TreeImpl>
TreeALG<TreeImpl>::~TreeALG()
{
}

template<typename TreeImpl>
void TreeALG<TreeImpl>::deleteNode(iterator const & it_p)
{
    impl_m.deleteNode(it_p);
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::iterator 
TreeALG<TreeImpl>::addChildren(iterator const &it_p, NodeContentALG &content_p)
{
    return impl_m.addChildren(it_p,content_p);
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::iterator TreeALG<TreeImpl>::getRootNode()
{
    return impl_m.root();
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::ChildrenPool
TreeALG<TreeImpl>::getChildren(iterator const & it_p)
{
    return impl_m.getChildren(it_p);
}

template<typename TreeImpl>
bool TreeALG<TreeImpl>::hasChildren(iterator const & it_p)
{
    return impl_m.hasChildren(it_p);
}

template<typename TreeImpl>
std::string
TreeALG<TreeImpl>::toString(const std::string &header_p)
{
    return toString(header_p, getRootNode());
}
template<typename TreeImpl>
std::string
TreeALG<TreeImpl>::toString(const std::string &header_p, const iterator &it_p)
{
    std::string res_l = header_p + "(" + (*it_p).toString() + ")\n";
    ChildrenPool children_l = getChildren(it_p);

    for (typename ChildrenPool::const_iterator it_l = children_l.begin();
         it_l != children_l.end(); ++it_l) {
        res_l += toString(header_p + "  ", *it_l);
    }

    return res_l;
}

#endif //TREEALGDEFS_HH_
