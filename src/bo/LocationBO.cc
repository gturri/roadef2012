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

#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ServiceBO.hh"
#include <boost/foreach.hpp>

LocationBO::LocationBO(int id_p) :
    id_m(id_p)
{}

void LocationBO::addMachine(MachineBO* machine_p){
    machines_m.insert(machine_p->getId());
}

void LocationBO::addMachine(int idxMachine_p){
    machines_m.insert(idxMachine_p);
}

int LocationBO::getId() const{
    return id_m;
}

unordered_set<int> LocationBO::getMachines() const {
	return machines_m;
}

bool LocationBO::operator==(const LocationBO& loc_p) const {
    if ( id_m != loc_p.id_m || machines_m.size() != loc_p.machines_m.size()){
        return false;
    }

    BOOST_FOREACH(int idxMachine_l, machines_m){
        if ( loc_p.machines_m.find(idxMachine_l) == loc_p.machines_m.end() ){
            return false;
        }
    }

    return true;
}

bool LocationBO::operator!=(const LocationBO& loc_p) const{
    return !this->operator==(loc_p);
}
