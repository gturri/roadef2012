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

#ifndef TREEALG_HH
#define TREEALG_HH

#include "DecisionALG.hh"

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <stdint.h>

/** Structure contenant l'information utile du noeud d'un point de vue
    recherche de solution. Quelque soit la structure de l'arbre, on en
    aura toujours besoin.
*/

struct NodeContentALG
{
    uint32_t nbSimu_m;
    float sumEval_m;
    DecisionALG * pDecision_m;

    NodeContentALG() : nbSimu_m(0), sumEval_m(0.0), pDecision_m(0) {}
    NodeContentALG(DecisionALG * pDecision_p) :
        nbSimu_m(0), sumEval_m(0.0), pDecision_m(pDecision_p)
    {}

    ~NodeContentALG()
    {
        // faudrait deleter là, mais si on delete, faut faire une copie pour le
        // move du vector...
        //delete pDecision_m;
    }

    // du coup on fait un clear manuel lors de la destruction d'un Node
    void clear() {delete pDecision_m; pDecision_m = 0; nbSimu_m = 0; sumEval_m = 0;}

    std::string toString() const
    {
        std::stringstream ss_l;
        ss_l << sumEval_m / nbSimu_m << "," << nbSimu_m;
        return ss_l.str();
    }
};

/** Classe servant d'interface pour l'arbre au sein de la MCTS.
 * Cette classe necessite en parametre template une classe implementant
 * un arbre. Il est conseille que cet arbre depende lui meme (template ou pas)
 * de la structure NodeContentALG ci dessus.
 * On utilise un iterateur pour gerer le deplacement dans l'arbre.
 */

template <typename TreeImpl>
class TreeALG
{
public:
    TreeALG();
    ~TreeALG();

    typedef typename TreeImpl::iterator iterator;
    typedef std::vector<iterator> ChildrenPool;

    // renvoie un iterateur sur la racine
    iterator root();

    // renvoie vrai si un iterateur a des fils
    bool hasChildren(iterator const &);

    // renvoie la liste des fils d'un iterateur
    ChildrenPool children(iterator const &);

    // detruit le noeud de l'iterateur qui devient donc invalide
    void deleteNode(iterator &);

    // renvoie un iterateur sur le noeud courant?
    iterator addChildren(iterator &, NodeContentALG &);

    std::string toString(int = -1);
    std::string toString(int, iterator const &);

private:
    TreeImpl impl_m;
};

#endif
