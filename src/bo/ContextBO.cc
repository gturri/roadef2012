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
    for ( vector<RessourceBO*>::iterator it_l=vpRessources_m.begin() ; it_l != vpRessources_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<MachineBO*>::iterator it_l = vpMachines_m.begin() ; it_l != vpMachines_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<LocationBO*>::iterator it_l = vpLocations_m.begin() ; it_l != vpLocations_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<NeighborhoodBO*>::iterator it_l = vpNeighborhoods_m.begin() ; it_l != vpNeighborhoods_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<ServiceBO*>::iterator it_l = vpServices_m.begin() ; it_l != vpServices_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<ProcessBO*>::iterator it_l = vpProcesses_m.begin() ; it_l != vpProcesses_m.end() ; it_l++ ){
        delete *it_l;
    }

    for ( vector<BalanceCostBO*>::iterator it_l = vpBalanceCosts_m.begin() ; it_l != vpBalanceCosts_m.end() ; it_l++ ){
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
   vpRessources_m.push_back(pRess_p);
}

int ContextBO::getNbRessources() const{
    return vpRessources_m.size();
}

RessourceBO* ContextBO::getRessource(int id_p) const{
    return vpRessources_m[id_p];
}

void ContextBO::addLocation(LocationBO* pLoc_p){
    vpLocations_m.push_back(pLoc_p);
}

int ContextBO::getNbLocations() const{
    return vpLocations_m.size();
}

LocationBO* ContextBO::getLocation(int idx_p) const{
    return vpLocations_m[idx_p];
}

void ContextBO::addNeighborhood(NeighborhoodBO* pNeigh_p){
    vpNeighborhoods_m.push_back(pNeigh_p);
}

int ContextBO::getNbNeighborhoods() const{
    return vpNeighborhoods_m.size();
}

NeighborhoodBO* ContextBO::getNeihborhood(int idx_p) const{
    return vpNeighborhoods_m[idx_p];
}

void ContextBO::addMachine(MachineBO* pMachine_p){
    vpMachines_m.push_back(pMachine_p);
}

int ContextBO::getNbMachines() const{
    return vpMachines_m.size();
}

MachineBO* ContextBO::getMachine(int idx_p) const{
    return vpMachines_m[idx_p];
}

void ContextBO::addService(ServiceBO* pService_p){
    vpServices_m.push_back(pService_p);
}

int ContextBO::getNbServices() const{
    return vpServices_m.size();
}

ServiceBO* ContextBO::getService(int idx_p) const{
    return vpServices_m[idx_p];
}

void ContextBO::addProcess(ProcessBO* pProcess_p){
    vpProcesses_m.push_back(pProcess_p);
}

int ContextBO::getNbProcesses() const{
    return vpProcesses_m.size();
}

ProcessBO* ContextBO::getProcess(int idx_p) const{
    return vpProcesses_m[idx_p];
}

void ContextBO::addBalanceCost(BalanceCostBO* pBalanceCost_p){
    vpBalanceCosts_m.push_back(pBalanceCost_p);
}

int ContextBO::getNbBalanceCosts() const{
    return vpBalanceCosts_m.size();
}

BalanceCostBO* ContextBO::getBalanceCost(int idx_p) const{
    return vpBalanceCosts_m[idx_p];
}

void ContextBO::setPoidsPMC(int poids_p){
    poidsPMC_m = poids_p;
}

int ContextBO::getPoidsPMC() const{
    return poidsPMC_m;
}

void ContextBO::setPoidsSMC(int poids_p){
    poidsSMC_m = poids_p;
}

int ContextBO::getPoidsSMC() const{
    return poidsSMC_m;
}

void ContextBO::setPoidsMMC(int poids_p){
    poidsMMC_m = poids_p;
}

int ContextBO::getPoidsMMC() const{
    return poidsMMC_m;
}

