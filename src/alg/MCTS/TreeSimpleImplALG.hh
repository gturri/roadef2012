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
    ChildrenPool children(iterator const &);
    
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
