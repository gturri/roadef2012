#include "GecodeSpace.hh"
#include "tools/Log.hh"

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

std::vector<int> GecodeSpace::solution()
{
    SpaceStatus status_l = status();
    assert(status_l == SS_SOLVED && machine_m.assigned());
    std::vector<int> res_l;

    for (IntVarArray::const_iterator it_l = machine_m.begin();
         it_l != machine_m.end(); ++it_l) {
        res_l.push_back(it_l->val());
    }

    return res_l;
}

void GecodeSpace::addDecision(const CPDecisionALG *pDecision_p)
{
    dom(*this, machine_m[pDecision_p->target_m], pDecision_p->min_m, pDecision_p->max_m);
}

GecodeSpace::DecisionPool GecodeSpace::generateDecisions()
{
    DecisionPool res_l;

    if (status() != SS_BRANCH)
        return res_l;

    // find the bigest var
    int target_l = 0;
    IntVar toBranch_l = machine_m[0];
    for (int i_l = 1; i_l < machine_m.size(); ++i_l)
        if (machine_m[i_l].size() > toBranch_l.size()) {
            toBranch_l = machine_m[i_l];
            target_l = i_l;
        }

    // for the moment, simple median branching
    res_l.push_back(new CPDecisionALG(target_l, toBranch_l.min(), toBranch_l.med()));
    res_l.push_back(new CPDecisionALG(target_l, toBranch_l.med() + 1, toBranch_l.max()));

    return res_l;
}
