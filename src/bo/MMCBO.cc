#include "bo/MMCBO.hh"
#include "bo/MachineBO.hh"

MMCBO::MMCBO(const vector<vector<int> >& costs_p) :
    costs_m(costs_p)
{}

int MMCBO::getCost(MachineBO* from_p, MachineBO* to_p) const {
    return costs_m[from_p->getId()][to_p->getId()];
}

int MMCBO::getCost(int idxMachineFrom_p, int idxMachineTo_p) const{
    return costs_m[idxMachineFrom_p][idxMachineTo_p];
}
