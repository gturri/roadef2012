#ifndef TREEALGDEFS_HH_
#define TREEALGDEFS_HH_

#include "TreeALG.hh"
#include "tools/Log.hh"

template<typename TreeImpl>
TreeALG<TreeImpl>::TreeALG()
{
}

template<typename TreeImpl>
TreeALG<TreeImpl>::~TreeALG()
{
}

template<typename TreeImpl>
void TreeALG<TreeImpl>::deleteNode(iterator & it_p)
{
    impl_m.deleteNode(it_p);
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::iterator 
TreeALG<TreeImpl>::addChildren(iterator &it_p, NodeContentALG &content_p)
{
    return impl_m.addChildren(it_p,content_p);
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::iterator TreeALG<TreeImpl>::root()
{
    return impl_m.root();
}

template<typename TreeImpl>
typename TreeALG<TreeImpl>::ChildrenPool
TreeALG<TreeImpl>::children(iterator const & it_p)
{
    return impl_m.children(it_p);
}

template<typename TreeImpl>
bool TreeALG<TreeImpl>::hasChildren(iterator const & it_p)
{
    return impl_m.hasChildren(it_p);
}

template<typename TreeImpl>
std::string
TreeALG<TreeImpl>::toString(int level_p, const std::string &header_p)
{
    return toString(level_p, header_p, root());
}
template<typename TreeImpl>
std::string
TreeALG<TreeImpl>::toString(int level_p, const std::string &header_p,
                            const iterator &it_p)
{
    std::string res_l = header_p + "(" + (*it_p).toString() + ")\n";
    ChildrenPool children_l = children(it_p);

    if (level_p != 0)
    for (typename ChildrenPool::const_iterator it_l = children_l.begin();
         it_l != children_l.end(); ++it_l) {
        res_l += toString(level_p - 1, header_p + "  ", *it_l);
    }

    return res_l;
}

#endif //TREEALGDEFS_HH_
