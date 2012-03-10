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

#include "bo/BalanceCostBO.hh"
#include "bo/RessourceBO.hh"

BalanceCostBO::BalanceCostBO(RessourceBO* pRess1_p, RessourceBO* pRess2_p, int target_p, int poids_p) :
    pRess1_m(pRess1_p),
    pRess2_m(pRess2_p),
    target_m(target_p),
    poids_m(poids_p)
{}

RessourceBO* BalanceCostBO::getRessource1() const{
    return pRess1_m;
}

RessourceBO* BalanceCostBO::getRessource2() const{
    return pRess2_m;
}

int BalanceCostBO::getTarget() const{
    return target_m;
}

int BalanceCostBO::getPoids() const{
    return poids_m;
}

bool BalanceCostBO::operator==(const BalanceCostBO& bc_p) const{
    return pRess1_m->getId() == bc_p.pRess1_m->getId()
        && pRess2_m->getId() == bc_p.pRess2_m->getId()
        && target_m == bc_p.target_m
        && poids_m == bc_p.poids_m;
}

bool BalanceCostBO::operator!=(const BalanceCostBO& bc_p) const {
    return !this->operator==(bc_p);
}

