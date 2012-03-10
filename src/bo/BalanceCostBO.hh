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

#ifndef BALANCECOSTBO_HH
#define BALANCECOSTBO_HH

class RessourceBO;

/**
 * Les balance costs interviennent dans la fonction objectif.
 * Un balance cost donne ajoute un cout egal a :
 *
 * poids_m * (somme sur les machine de : [ max(0, target_m*A(m, pRess1_m), - 1(m, pRess2_m) ] )
 *
 * ou A(m, pRess_m) = C(m, pRess_m) - U(m, pRess_m), cad la quantite de pRess_m encore dispo
 */
class BalanceCostBO{
    public:
        BalanceCostBO(RessourceBO* pRess1_p, RessourceBO* pRess2_p, int target_p, int poids_p);

        RessourceBO* getRessource1() const;
        RessourceBO* getRessource2() const;
        int getTarget() const;
        int getPoids() const;

        bool operator==(const BalanceCostBO& bc_p) const;
        bool operator!=(const BalanceCostBO& bc_p) const;


    private:
        RessourceBO* const pRess1_m;
        RessourceBO* const pRess2_m;
        const int target_m;
        const int poids_m;
};

#endif
