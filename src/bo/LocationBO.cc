#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ServiceBO.hh"

LocationBO::LocationBO(int id_p) :
    id_m(id_p)
{}

void LocationBO::addMachine(MachineBO* machine_p){
    machines_m.insert(machine_p);
}

int LocationBO::getId() const{
    return id_m;
}
