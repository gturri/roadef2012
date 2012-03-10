/*
 * Copyright (c) 2011 Pierre-Etienne Bougué <pe.bougue(a)gmail.com>
 * Copyright (c) 2011 Florian Colin <florian.colin28(a)gmail.com>
 * Copyright (c) 2011 Kamal Fadlaoui <kamal.fadlaoui(a)gmail.com>
 * Copyright (c) 2011 Quentin Lequy <quentin.lequy(a)gmail.com>
 * Copyright (c) 2011 Guillaume Pinot <guillaume.pinot(a)tremplin-utc.net>
 * Copyright (c) 2011 Cédric Royer <cedroyer(a)gmail.com>
 * Copyright (c) 2011 Guillaume Turri <guillaume.turri(a)gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

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
    iterator root_l = root();
    deleteNode(root_l);
}


template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator 
    TreeSimpleImplALG<NodeContent>::root()
{
    return iterator(&root_m);
}

template <class NodeContent>
void TreeSimpleImplALG<NodeContent>::deleteNode(iterator &it_p)
{
    // on delete les fils
    ChildrenList &children_l = it_p.pNode_m->children_m;
    while (children_l.size() != 0) {
        iterator itChild_l(it_p, 0);
        deleteNode(itChild_l);
    }

    it_p->clear();
    if(it_p.path_m.size() != 0) {
        // on delete le node si c'est pas root
        ChildrenList &cl_l = it_p.path_m.back().first->children_m;
        size_t idx_l = it_p.path_m.back().second;
        cl_l.erase(cl_l.begin() + idx_l);
    }

    // clear the iterator for bug visibility
    it_p.pNode_m = 0;
    it_p.path_m.clear();
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::iterator
TreeSimpleImplALG<NodeContent>::addChildren(iterator &it_p,
                                            const NodeContent &content_p)
{
    it_p.pNode_m->children_m.push_back(Node(content_p,ChildrenList()));
    return iterator(it_p, it_p.pNode_m->children_m.size() - 1);
}

template <class NodeContent>
bool TreeSimpleImplALG<NodeContent>::hasChildren(const iterator & it_p)
{
	return (it_p.pNode_m->children_m.size() != 0);
}

template <class NodeContent>
typename TreeSimpleImplALG<NodeContent>::ChildrenPool 
    TreeSimpleImplALG<NodeContent>::children(const iterator & it_p)
{
    ChildrenPool pool_l;
    const ChildrenList &list_l = it_p.pNode_m->children_m;

    for (size_t i_l = 0; i_l < list_l.size(); ++i_l) {
        pool_l.push_back(iterator(it_p, i_l));
    }
    
    return pool_l;
}

#endif //TREESIMPLEIMPLALGDEFS_HH_
