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

#include "dtoin/RessourceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "tools/Log.hh"
#include <cassert>

void RessourceDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbRess_l;
    is_p >> nbRess_l;
    LOG(DEBUG) << nbRess_l << " ressources" << endl;
    assert(nbRess_l > 0);

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        bool isTransient_l;
        is_p >> isTransient_l;
        int weightLoadCost_l;
        is_p >> weightLoadCost_l;
        LOG(DEBUG) << "\tRessource " << idxRess_l << " : isTransient=" << isTransient_l << ", poids=" << weightLoadCost_l << endl;

        pContextBO_p->addRessource(new RessourceBO(idxRess_l, isTransient_l, weightLoadCost_l));
    }
};
