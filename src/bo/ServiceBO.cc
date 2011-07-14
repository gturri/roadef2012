#include "bo/ServiceBO.hh"
#include "bo/ProcessBO.hh"


ServiceBO::ServiceBO(int id_p, int spreadMin_p, const unordered_set<int>& sDependances_p) :
    id_m(id_p),
    spreadMin_m(spreadMin_p),
    sIDependOnThem_m(sDependances_p)
{}

int ServiceBO::getId() const{
    return id_m;
}

int ServiceBO::getSpreadMin() const {
    return spreadMin_m;
}

int ServiceBO::getNbServicesIDependOn() const{
    return sIDependOnThem_m.size();
}

bool ServiceBO::iDependOn(int idx_p) const{
    return sIDependOnThem_m.find(idx_p) != sIDependOnThem_m.end();
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

unordered_set<int> ServiceBO::getServicesIDependOn() const{
    return sIDependOnThem_m;
}
