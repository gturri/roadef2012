#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <boost/foreach.hpp>

ContextBO::ContextBO() :
    pMMCBO_m(0)
{}

ContextBO::ContextBO(const ContextBO& contextBO_p){
    BOOST_FOREACH(RessourceBO* pRess_l, contextBO_p.vpRessources_m){
        vpRessources_m.push_back(new RessourceBO(*pRess_l));
    }
    BOOST_FOREACH(LocationBO* pLoc_l, contextBO_p.vpLocations_m){
        vpLocations_m.push_back(new LocationBO(*pLoc_l));
    }
    BOOST_FOREACH(NeighborhoodBO* pNeigh_l, contextBO_p.vpNeighborhoods_m){
        vpNeighborhoods_m.push_back(new NeighborhoodBO(*pNeigh_l));
    }
    BOOST_FOREACH(MachineBO* pMachine_l, contextBO_p.vpMachines_m){
        LocationBO* pLoc_l = vpLocations_m[pMachine_l->getLocation()->getId()];
        NeighborhoodBO* pNeigh_l = vpNeighborhoods_m[pMachine_l->getNeighborhood()->getId()];
        vpMachines_m.push_back(new MachineBO(pMachine_l->getId(), pLoc_l, pNeigh_l, pMachine_l->getCapas(), pMachine_l->getSafetyCapas()));
    }
    BOOST_FOREACH(ServiceBO* pService_l, contextBO_p.vpServices_m){
        vpServices_m.push_back(new ServiceBO(*pService_l));
    }
    BOOST_FOREACH(ProcessBO* pProcess_l, contextBO_p.vpProcesses_m){
        ServiceBO* pService_l = vpServices_m[pProcess_l->getService()->getId()];
        vpProcesses_m.push_back(new ProcessBO(pProcess_l->getId(), pService_l, pProcess_l->getRequirements(), pProcess_l->getPMC()));
        vpProcesses_m.back()->setMachineInit(vpMachines_m[pProcess_l->getMachineInit()->getId()]);
    }
    BOOST_FOREACH(BalanceCostBO* pBC_l, contextBO_p.vpBalanceCosts_m){
        RessourceBO* pRess1_l = vpRessources_m[pBC_l->getRessource1()->getId()];
        RessourceBO* pRess2_l = vpRessources_m[pBC_l->getRessource2()->getId()];
        vpBalanceCosts_m.push_back(new BalanceCostBO(pRess1_l, pRess2_l, pBC_l->getTarget(), pBC_l->getPoids()));
    }
    pMMCBO_m = new MMCBO(*(contextBO_p.pMMCBO_m));

    poidsPMC_m = contextBO_p.poidsPMC_m;
    poidsSMC_m = contextBO_p.poidsSMC_m;
    poidsMMC_m = contextBO_p.poidsMMC_m;
}

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

/* FIXME : la duplication de code se fait pleinement sentir ici.
 * (plutot que de trouver une rustine pour ne corriger que cette methode,
 * il est p.e. plus pertinent de refactorer totalement la classe...)
 */
bool ContextBO::operator==(const ContextBO& context_p) const{
    //Ressources
    if ( vpRessources_m.size() != context_p.vpRessources_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpRessources_m.size() ; idx_l++ ){
        if ( *(vpRessources_m[idx_l]) != *(context_p.vpRessources_m[idx_l]) ){
            return false;
        }
    }

    //Machines
    if ( vpMachines_m.size() != context_p.vpMachines_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpMachines_m.size() ; idx_l++ ){
        if ( *(vpMachines_m[idx_l]) != *(context_p.vpMachines_m[idx_l]) ){
            return false;
        }
    }

    //Locations
    if ( vpLocations_m.size() != context_p.vpLocations_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpLocations_m.size() ; idx_l++ ){
        if ( *(vpLocations_m[idx_l]) != *(context_p.vpLocations_m[idx_l]) ){
            return false;
        }
    }

    //Neighborhoods
    if ( vpNeighborhoods_m.size() != context_p.vpNeighborhoods_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpNeighborhoods_m.size() ; idx_l++ ){
        if ( *(vpNeighborhoods_m[idx_l]) != *(context_p.vpNeighborhoods_m[idx_l]) ){
            return false;
        }
    }

    //Services
    if ( vpServices_m.size() != context_p.vpServices_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpServices_m.size() ; idx_l++ ){
        if ( *(vpServices_m[idx_l]) != *(context_p.vpServices_m[idx_l]) ){
            return false;
        }
    }

    //Process
    if ( vpProcesses_m.size() != context_p.vpProcesses_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpProcesses_m.size() ; idx_l++ ){
        if ( *(vpProcesses_m[idx_l]) != *(context_p.vpProcesses_m[idx_l]) ){
            return false;
        }
    }

    //Balances Costs
    if ( vpBalanceCosts_m.size() != context_p.vpBalanceCosts_m.size() ){
        return false;
    }
    for ( size_t idx_l=0 ; idx_l < vpBalanceCosts_m.size() ; idx_l++ ){
        if ( *(vpBalanceCosts_m[idx_l]) != *(context_p.vpBalanceCosts_m[idx_l]) ){
            return false;
        }
    }


    //Autres attributs
    return *pMMCBO_m == *(context_p.pMMCBO_m)
        && poidsPMC_m == context_p.poidsPMC_m
        && poidsSMC_m == context_p.poidsSMC_m
        && poidsMMC_m == context_p.poidsMMC_m;
}
