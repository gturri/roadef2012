#include "gtests/tools/CheckerFixture.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/ServiceBO.hh"

ProcessBO* CheckerFixture::buildProcess(int idP_p, ServiceBO* pService_p, const vector<int>& vRequirements_p, int pmc_p, int idxMachineInit_p, ContextBO* pContextBO_p) {
    ProcessBO* pProcess_l = new ProcessBO(idP_p, pService_p, vRequirements_p, pmc_p);
    pProcess_l->setMachineInit(pContextBO_p->getMachine(idxMachineInit_p));
    pContextBO_p->addProcess(pProcess_l);
    return pProcess_l;
}

ServiceBO* CheckerFixture::buildService(int idS_p, int spreadMin_p, const unordered_set<int>& sDependances_p, ContextBO* pContextBO_p){
    ServiceBO* pService_l = new ServiceBO(idS_p, spreadMin_p, sDependances_p);
    pContextBO_p->addService(pService_l);
    return pService_l;
}

LocationBO* CheckerFixture::buildLocation(int idLoc_p, ContextBO* pContextBO_p){
    LocationBO* pLoc_l = new LocationBO(idLoc_p);
    pContextBO_p->addLocation(pLoc_l);
    return pLoc_l;
}

NeighborhoodBO* CheckerFixture::buildNeigh(int idNeigh_p, ContextBO* pContextBO_p){
    NeighborhoodBO* pNeigh_l = new NeighborhoodBO(idNeigh_p);
    pContextBO_p->addNeighborhood(pNeigh_l);
    return pNeigh_l;
}

MachineBO* CheckerFixture::buildMachine(int idMachine_p, int idLoc_p, int idNeigh_p, const vector<int>& capa_p, const vector<int>& safetyCapa_p, ContextBO* pContextBO_p){
    for ( int idxLoc_l=pContextBO_p->getNbLocations() ; idxLoc_l <= idLoc_p ; idxLoc_l++ ){
        buildLocation(idxLoc_l, pContextBO_p);
    }

    for ( int idxNeigh_l=pContextBO_p->getNbNeighborhoods() ; idxNeigh_l <= idNeigh_p ; idxNeigh_l++ ){
        buildNeigh(idxNeigh_l, pContextBO_p);
    }

    MachineBO* pMachine_l = new MachineBO(idMachine_p,
            pContextBO_p->getLocation(idLoc_p),
            pContextBO_p->getNeighborhood(idNeigh_p),
            capa_p,
            safetyCapa_p);
    pContextBO_p->addMachine(pMachine_l);
    return pMachine_l;
}
