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

#include "dtoin/ProcessDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "tools/Log.hh"
#include <cassert>
#include <vector>
using namespace std;

void ProcessDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l, nbRessources_l(pContextBO_p->getNbRessources());
    is_p >> nbProcesses_l;
    LOG(DEBUG) << nbProcesses_l << " processes" << endl;
    assert(nbProcesses_l > 0);


    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxService_l, pmc_l;
        is_p >> idxService_l;
        assert(idxService_l >= 0);
        vector<int> vRequirements_l(nbProcesses_l, 0);

        for ( int idxRess_l=0 ; idxRess_l < nbRessources_l ; idxRess_l++ ){
            is_p >> vRequirements_l[idxRess_l];
        }

        is_p >> pmc_l;
        LOG(DEBUG) << "\tLe process " << idxP_l << " est dans le service " << idxService_l << " et a un pmc de " << pmc_l << endl;

        pContextBO_p->addProcess(new ProcessBO(idxP_l, pContextBO_p->getService(idxService_l), vRequirements_l, pmc_l));
    }
}
