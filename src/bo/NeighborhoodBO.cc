#include "bo/NeighborhoodBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ServiceBO.hh"

NeighborhoodBO::NeighborhoodBO(int id_p) :
    id_m(id_p)
{}

void NeighborhoodBO::addMachine(MachineBO* machine_p){
    machines_m.insert(machine_p->getId());
}

int NeighborhoodBO::getId() const{
    return id_m;
}
