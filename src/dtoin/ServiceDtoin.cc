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

#include "dtoin/ServiceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ServiceBO.hh"
#include "tools/Log.hh"
#include <cassert>
#include <tr1/unordered_set>
using namespace std;

void ServiceDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbServices_l;
    is_p >> nbServices_l;
    LOG(DEBUG) << nbServices_l << " services" << endl;

    for ( int idxService_l=0 ; idxService_l < nbServices_l ; idxService_l++ ){
        int spreadMin_l, nbDependances_l;
        is_p >> spreadMin_l >> nbDependances_l;
        LOG(DEBUG) << "\tService " << idxService_l << " : spread min=" << spreadMin_l << ", nb dependances=" << nbDependances_l << endl;
        unordered_set<int> dependances_l;

        for ( int idxDep_l=0 ; idxDep_l < nbDependances_l ; idxDep_l++ ){
            int idxServiceDep_l;
            is_p >> idxServiceDep_l;
            dependances_l.insert(idxServiceDep_l);
        }

        pContextBO_p->addService(new ServiceBO(idxService_l, spreadMin_l, dependances_l));
    }
}
