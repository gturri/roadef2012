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

vector<int> MachineBO::getCapas() const{
    return capa_m;
}

int MachineBO::getSafetyCapa(int idxRess_p) const{
    return safetyCapa_m[idxRess_p];
}

vector<int> MachineBO::getSafetyCapas() const{
    return safetyCapa_m;
}
