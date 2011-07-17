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
