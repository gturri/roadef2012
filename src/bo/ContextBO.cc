#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"

ContextBO::ContextBO() :
    pMMCBO_m(0)
{}

ContextBO::~ContextBO(){
    for ( vector<RessourceBO*>::iterator it_l=ressources_m.begin() ; it_l != ressources_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<MachineBO*>::iterator it_l = machines_m.begin() ; it_l != machines_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<LocationBO*>::iterator it_l = locations_m.begin() ; it_l != locations_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<NeighborhoodBO*>::iterator it_l = neighborhoods_m.begin() ; it_l != neighborhoods_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<ServiceBO*>::iterator it_l = services_m.begin() ; it_l != services_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<ProcessBO*>::iterator it_l = processes_m.begin() ; it_l != processes_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<BalanceCostBO*>::iterator it_l = balanceCosts_m.begin() ; it_l != balanceCosts_m.end() ; it_l++ ){
        delete *it_l;
    }

    delete pMMCBO_m;
}

void ContextBO::setMMCBO(MMCBO* pMMC_p){
    delete pMMCBO_m;
    pMMCBO_m = pMMC_p;
}

MMCBO* ContextBO::getMMCBO() const{
    return pMMCBO_m;
}

void ContextBO::addRessource(RessourceBO* pRess_p){
    ressources_m.push_back(pRess_p);
}

int ContextBO::getNbRessources() const{
    return ressources_m.size();
}

RessourceBO* ContextBO::getRessource(int id_p) const{
    return ressources_m[id_p];
}

void ContextBO::addLocation(LocationBO* pLoc_p){
    locations_m.push_back(pLoc_p);
}

int ContextBO::getNbLocations() const{
    return locations_m.size();
}

LocationBO* ContextBO::getLocation(int idx_p) const{
    return locations_m[idx_p];
}

void ContextBO::addNeighborhood(NeighborhoodBO* pNeigh_p){
    neighborhoods_m.push_back(pNeigh_p);
}

int ContextBO::getNbNeighborhoods() const{
    return neighborhoods_m.size();
}

NeighborhoodBO* ContextBO::getNeihborhood(int idx_p) const{
    return neighborhoods_m[idx_p];
}

void ContextBO::addMachine(MachineBO* pMachine_p){
    machines_m.push_back(pMachine_p);
}

int ContextBO::getNbMachines() const{
    return machines_m.size();
}

MachineBO* ContextBO::getMachine(int idx_p) const{
    return machines_m[idx_p];
}

void ContextBO::addService(ServiceBO* pService_p){
    services_m.push_back(pService_p);
}

int ContextBO::getNbServices() const{
    return services_m.size();
}

ServiceBO* ContextBO::getService(int idx_p) const{
    return services_m[idx_p];
}

void ContextBO::addProcess(ProcessBO* pProcess_p){
    processes_m.push_back(pProcess_p);
}

int ContextBO::getNbProcesses() const{
    return processes_m.size();
}

ProcessBO* ContextBO::getProcess(int idx_p) const{
    return processes_m[idx_p];
}

void ContextBO::addBalanceCost(BalanceCostBO* pBalanceCost_p){
    balanceCosts_m.push_back(pBalanceCost_p);
}

int ContextBO::getNbBalanceCosts() const{
    return balanceCosts_m.size();
}

BalanceCostBO* ContextBO::getBalanceCost(int idx_p) const{
    return balanceCosts_m[idx_p];
}
