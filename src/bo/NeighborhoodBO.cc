#include "bo/NeighborhoodBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ServiceBO.hh"
#include <boost/foreach.hpp>

NeighborhoodBO::NeighborhoodBO(int id_p) :
    id_m(id_p)
{}

void NeighborhoodBO::addMachine(MachineBO* machine_p){
    machines_m.insert(machine_p->getId());
}

void NeighborhoodBO::addMachine(int idxMachine_p){
    machines_m.insert(idxMachine_p);
}

int NeighborhoodBO::getId() const{
    return id_m;
}

bool NeighborhoodBO::operator==(const NeighborhoodBO& neigh_p) const{
    if ( id_m != neigh_p.id_m || machines_m.size() != neigh_p.machines_m.size() ){
        return false;
    }

    BOOST_FOREACH(int idxMachines_l, machines_m){
        if ( neigh_p.machines_m.find(idxMachines_l) == neigh_p.machines_m.end() ){
            return false;
        }
    }

    return true;
}

unordered_set<int> NeighborhoodBO::getMachines() const{
	return machines_m;
}

bool NeighborhoodBO::operator!=(const NeighborhoodBO& neigh_p) const{
    return !this->operator==(neigh_p);
}
