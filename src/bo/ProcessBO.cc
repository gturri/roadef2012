#include "bo/ProcessBO.hh"
#include "bo/MachineBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"

ProcessBO::ProcessBO(int id_p, ServiceBO* pService_p, const vector<int>& vRequirements_p,  int pmc_p) :
    id_m(id_p),
    pService_m(pService_p),
    vRequirements_m(vRequirements_p),
    pMachineInit_m(0),
    pmc_m(pmc_p)
{
    pService_m->addProcess(this);
}

int ProcessBO::getId() const{
    return id_m;
}

ServiceBO* ProcessBO::getService() const{
    return pService_m;
}

int ProcessBO::getRequirement(int idxRess_p) const{
    return vRequirements_m[idxRess_p];
}

vector<int> ProcessBO::getRequirements() const{
    return vRequirements_m;
}

void ProcessBO::setMachineInit(MachineBO* pMachine_p){
    pMachineInit_m = pMachine_p;
}

MachineBO* ProcessBO::getMachineInit() const{
    return pMachineInit_m;
}

int ProcessBO::getPMC() const{
    return pmc_m;
}

bool ProcessBO::operator==(const ProcessBO& process_p) const {
    return id_m == process_p.id_m
        && pService_m->getId() == process_p.pService_m->getId()
        && vRequirements_m == process_p.vRequirements_m
        && pMachineInit_m->getId() == process_p.pMachineInit_m->getId()
        && pmc_m == process_p.pmc_m;
}

bool ProcessBO::operator!=(const ProcessBO& process_p) const{
    return ! this->operator==(process_p);
}
