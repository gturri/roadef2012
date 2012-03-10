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
TreeALG<TreeImpl>::toString(int level_p)
{
    return toString(level_p, root());
}
template<typename TreeImpl>
std::string
TreeALG<TreeImpl>::toString(int level_p, const iterator &it_p)
{
    std::string res_l = "(" + it_p->toString() + ")";
    ChildrenPool children_l = children(it_p);

    if (level_p != 0) {
        typename ChildrenPool::const_iterator it_l = children_l.begin();

        if (it_l != children_l.end()) {
            res_l += "{" + toString(level_p - 1, *it_l);

            for (++it_l; it_l != children_l.end(); ++it_l)
                res_l += ";" + toString(level_p - 1, *it_l);

            res_l += "}";
        }
    }

    return res_l;
}

#endif //TREEALGDEFS_HH_
