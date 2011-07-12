#include "generateur/alg/DummyStrategyGeneration.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"

list<shared_ptr<ContextBO> > DummyStrategyGeneration::generate(const variables_map& arg_p){
    shared_ptr<ContextBO> pContextBO_l(new ContextBO);

    buildRessources(pContextBO_l);
    buildMachines(pContextBO_l);
    buildMMC(pContextBO_l);
    buildServices(pContextBO_l);
    buildProcesses(pContextBO_l);
    buildBalanceCosts(pContextBO_l);
    buildPoids(pContextBO_l);

    list<shared_ptr<ContextBO> > result_l;
    result_l.push_back(pContextBO_l);

    return result_l;
}

void DummyStrategyGeneration::buildRessources(shared_ptr<ContextBO> pContextBO_p){
    pContextBO_p->addRessource(new RessourceBO(0, false, 15));
}

void DummyStrategyGeneration::buildMachines(shared_ptr<ContextBO> pContextBO_p){
    LocationBO* pLoc_l = new LocationBO(0);
    NeighborhoodBO* pNeigh_l = new NeighborhoodBO(0);
    vector<int> vCapa_p(1, 5);
    vector<int> vSafetyCapa_l(1, 3);
    pContextBO_p->addLocation(pLoc_l);
    pContextBO_p->addNeighborhood(pNeigh_l);
    pContextBO_p->addMachine(new MachineBO(0, pLoc_l, pNeigh_l, vCapa_p, vSafetyCapa_l));
} 

void DummyStrategyGeneration::buildMMC(shared_ptr<ContextBO> pContextBO_p){
    pContextBO_p->setMMCBO(new MMCBO(vector<vector<int> >(1, vector<int>(1, 0))));
}

void DummyStrategyGeneration::buildServices(shared_ptr<ContextBO> pContextBO_p){
    unordered_set<int> dependances_l;
    pContextBO_p->addService(new ServiceBO(0, 1, dependances_l));
}

void DummyStrategyGeneration::buildProcesses(shared_ptr<ContextBO> pContextBO_p){
    ServiceBO* pService_l = pContextBO_p->getService(0);
    vector<int> vRequire_l(1, 1);
    ProcessBO* pProcess_l = new ProcessBO(0, pService_l, vRequire_l, 0);
    pContextBO_p->addProcess(pProcess_l);
    pProcess_l->setMachineInit(pContextBO_p->getMachine(0));
}

void DummyStrategyGeneration::buildBalanceCosts(shared_ptr<ContextBO> pContextBO_p){}

void DummyStrategyGeneration::buildPoids(shared_ptr<ContextBO> pContextBO_p){
    pContextBO_p->setPoidsPMC(42);
    pContextBO_p->setPoidsSMC(69);
    pContextBO_p->setPoidsMMC(1664);
}
