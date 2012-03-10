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

#include "bo/ServiceBO.hh"
#include "bo/ProcessBO.hh"
#include <boost/foreach.hpp>


ServiceBO::ServiceBO(int id_p, int spreadMin_p, const unordered_set<int>& sDependances_p) :
    id_m(id_p),
    spreadMin_m(spreadMin_p),
    sIDependOnThem_m(sDependances_p)
{}

int ServiceBO::getId() const{
    return id_m;
}

int ServiceBO::getSpreadMin() const {
    return spreadMin_m;
}

int ServiceBO::getNbServicesIDependOn() const{
    return sIDependOnThem_m.size();
}

bool ServiceBO::iDependOn(int idx_p) const{
    return sIDependOnThem_m.find(idx_p) != sIDependOnThem_m.end();
}

void ServiceBO::addProcess(ProcessBO* pProcess_p){
    sProcess_m.insert(pProcess_p->getId());
}

int ServiceBO::getNbProcesses() const{
    return sProcess_m.size();
}

bool ServiceBO::containsProcess(int idxProcess_p) const{
    return sProcess_m.find(idxProcess_p) != sProcess_m.end();
}

unordered_set<int> ServiceBO::getProcesses() const{
    return sProcess_m;
}

unordered_set<int> ServiceBO::getServicesIDependOn() const{
    return sIDependOnThem_m;
}

bool ServiceBO::operator==(const ServiceBO& service_p) const {
    if ( id_m != service_p.id_m
        || sProcess_m.size() != service_p.sProcess_m.size()
        || spreadMin_m != service_p.spreadMin_m
        || sIDependOnThem_m.size() != service_p.sIDependOnThem_m.size()){
        return false;
    }

    BOOST_FOREACH(int idxP_l, sProcess_m){
        if ( service_p.sProcess_m.find(idxP_l) == service_p.sProcess_m.end() ){
            return false;
        }
    }

    BOOST_FOREACH(int idxDep_l, sIDependOnThem_m){
        if ( ! service_p.iDependOn(idxDep_l) ){
            return false;
        }
    }

    return true;
}

bool ServiceBO::operator!=(const ServiceBO& service_p) const{
    return !this->operator==(service_p);
}
