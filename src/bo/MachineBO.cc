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

#include "bo/MachineBO.hh"
#include "bo/LocationBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/RessourceBO.hh"


MachineBO::MachineBO(int id_p, LocationBO* location_p, NeighborhoodBO* neighborhood_p, const vector<int>& capa_p, const vector<int> safetyCapa_p) :
    id_m(id_p),
    location_m(location_p),
    neighborhood_m(neighborhood_p),
    capa_m(capa_p),
    safetyCapa_m(safetyCapa_p)
{
    location_m->addMachine(this);
    neighborhood_m->addMachine(this);
}

int MachineBO::getId() const{
    return id_m;
}

LocationBO* MachineBO::getLocation() const{
    return location_m;
}

NeighborhoodBO* MachineBO::getNeighborhood() const{
    return neighborhood_m;
}

int MachineBO::getCapa(int idxRess_p) const{
    return capa_m[idxRess_p];
}

int MachineBO::getCapa(RessourceBO const * pRess_p) const{
    return capa_m[pRess_p->getId()];
}

vector<int> MachineBO::getCapas() const{
    return capa_m;
}

int MachineBO::getSafetyCapa(int idxRess_p) const{
    return safetyCapa_m[idxRess_p];
}

vector<int> MachineBO::getSafetyCapas() const{
    return safetyCapa_m;
}

bool MachineBO::operator==(MachineBO& machine_p) const {
    return id_m == machine_p.id_m
        && location_m->getId() == machine_p.location_m->getId()
        && neighborhood_m->getId() == machine_p.neighborhood_m->getId()
        && capa_m == machine_p.capa_m
        && safetyCapa_m == machine_p.safetyCapa_m;
}

bool MachineBO::operator!=(MachineBO& machine_p) const{
    return ! (this->operator==(machine_p));
}
