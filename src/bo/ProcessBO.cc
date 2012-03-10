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

#include "bo/ProcessBO.hh"
#include "bo/MachineBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"

ProcessBO::ProcessBO(int id_p, ServiceBO* pService_p, const vector<int>& vRequirements_p,  int pmc_p) :
    id_m(id_p),
    pService_m(pService_p),
    vRequirements_m(vRequirements_p),
    pMachineInit_m(0),
    pmc_m(pmc_p)
{
    pService_m->addProcess(this);
}

int ProcessBO::getId() const{
    return id_m;
}

ServiceBO* ProcessBO::getService() const{
    return pService_m;
}

int ProcessBO::getRequirement(int idxRess_p) const{
    return vRequirements_m[idxRess_p];
}

int ProcessBO::getRequirement(RessourceBO const * pRess_p) const{
    return vRequirements_m[pRess_p->getId()];
}

vector<int> ProcessBO::getRequirements() const{
    return vRequirements_m;
}

void ProcessBO::setMachineInit(MachineBO* pMachine_p){
    pMachineInit_m = pMachine_p;
}

MachineBO* ProcessBO::getMachineInit() const{
    return pMachineInit_m;
}

int ProcessBO::getPMC() const{
    return pmc_m;
}

bool ProcessBO::operator==(const ProcessBO& process_p) const {
    return id_m == process_p.id_m
        && pService_m->getId() == process_p.pService_m->getId()
        && vRequirements_m == process_p.vRequirements_m
        && pMachineInit_m->getId() == process_p.pMachineInit_m->getId()
        && pmc_m == process_p.pmc_m;
}

bool ProcessBO::operator!=(const ProcessBO& process_p) const{
    return ! this->operator==(process_p);
}
