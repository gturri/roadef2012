#include "GecodeSpace.hh"

using namespace Gecode;

GecodeSpace::GecodeSpace(const ContextBO *pContext_p) :
    machine_m(*this, pContext_p->getNbProcesses(),
              0, pContext_p->getNbMachines() - 1)
{
    /*
    int nbProc_l = pContext_p->getNbProcesses();
    for (int res_l = 0; res_l < pContext_p->getNbRessources(); ++res_l) {
        RessourceBO *pRes_l = pContext_p->getRessource(res_l);
    }
    */

    // random branching to do a Monte Carlo generation
    branch(*this, machine_m, INT_VAR_SIZE_MIN, INT_VAL_RND);
}

GecodeSpace::GecodeSpace(bool share_p, GecodeSpace &that) :
    Space(share_p, that)
{
    machine_m.update(*this, share_p, that.machine_m);
}

Gecode::Space *GecodeSpace::copy(bool share_p)
{
    return new GecodeSpace(share_p, *this);
}

std::vector<int> GecodeSpace::solution() const
{
    return std::vector<int>();
}
