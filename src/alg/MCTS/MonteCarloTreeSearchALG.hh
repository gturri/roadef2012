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

#ifndef MONTECARLOTREESEARCHALG_HH
#define MONTECARLOTREESEARCHALG_HH

/** Classe qui effectue la recherche. A partir de l'arbre de decision, elle
    effectue une descente suivant la formule magique en replissant au fur et
    a mesure la classe SpaceALG courante. Par le biais de cette derniere, elle
    va ensuite generer les fils de la feuille courante puis lancer sur ceux-ci
    des simulations et des recherches locales a partir de l'espace courant.
    L'information est finalement remonter pour effectuer la prochaine descente.
 */

#include "TreeALG.hh"
#include "TreeSimpleImplALG.hh"

class SolutionALG;
class SpaceALG;

class MonteCarloTreeSearchALG
{
    public:
        typedef TreeALG< TreeSimpleImplALG<NodeContentALG> > Tree;
        
        MonteCarloTreeSearchALG();
        ~MonteCarloTreeSearchALG();
        
        void search();
        
        void setpTree(Tree *);
        Tree * getpTree() const;

        void setpInitialSpace(SpaceALG *); 
        
    private:
        SpaceALG * initNewSpace();
        int performDescent();
        
        Tree * pTree_m;
        SpaceALG * pInitialSpace_m;
};

#endif
