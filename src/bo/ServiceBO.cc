#include "bo/ServiceBO.hh"
#include "bo/ProcessBO.hh"


ServiceBO::ServiceBO(int id_p, int spreadMin_p, const unordered_set<int>& dependances_p) :
    id_m(id_p),
    spreadMin_m(spreadMin_p),
    iDependOnThem_m(dependances_p)
{}

int ServiceBO::getId() const{
    return id_m;
}

int ServiceBO::getSpreadMin() const {
    return spreadMin_m;
}

int ServiceBO::getNbServicesIDependOn() const{
    return iDependOnThem_m.size();
}

bool ServiceBO::iDependOn(int idx_p) const{
    return iDependOnThem_m.find(idx_p) != iDependOnThem_m.end();
}

void ServiceBO::addProcess(ProcessBO* pProcess_p){
    sProcess_m.insert(pProcess_p->getId());
}

int ServiceBO::getNbProcesses() const{
    return sProcess_m.size();
}

bool ServiceBO::containsProcess(int idxProcess_p) const{
    return sProcess_m.find(idxProcess_p) != sProcess_m.end();
}
