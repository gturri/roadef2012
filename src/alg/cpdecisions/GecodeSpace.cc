#ifdef USE_GECODE

#include "GecodeSpace.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "tools/Log.hh"

#include <gecode/minimodel.hh>

using namespace Gecode;

GecodeSpace::GecodeSpace(const ContextBO *pContext_p) :
    machine_m(*this, pContext_p->getNbProcesses(),
              0, pContext_p->getNbMachines() - 1)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();

    // matrix proc x mach
    BoolVarArgs tmpX_l(*this, nbProc_l * nbMach_l, 0, 1);
    Matrix<BoolVarArgs> x_l(tmpX_l, nbProc_l, nbMach_l);
       
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        channel(*this, x_l.col(proc_l), machine_m[proc_l]);

    /*
     * Capacity
     */
    for (int res_l = 0; res_l < pContext_p->getNbRessources(); ++res_l) {
        // facultative
        /*
        RessourceBO *pRes_l = pContext_p->getRessource(res_l);
        if (pRes_l->isTransient())
            continue;
        */

        IntVarArgs load_l(*this, nbMach_l, 0, Int::Limits::max);
        for (int mach_l = 0; mach_l < nbMach_l; ++mach_l) {
            MachineBO *pMach_l = pContext_p->getMachine(mach_l);
            int capa_l = pMach_l->getCapa(res_l);
            rel(*this, load_l[mach_l], IRT_LQ, capa_l);
        }

        IntArgs sizes_l(nbProc_l);
        int totalSize_l = 0;
        for (int proc_l = 0; proc_l < nbProc_l; ++proc_l) {
            ProcessBO *pProc_l = pContext_p->getProcess(proc_l);
            int req_l = pProc_l->getRequirement(res_l);
            sizes_l[proc_l] = req_l;
            totalSize_l += req_l;
        }

        /*
         * This is _the_ constraint for non transient resources, but seems too
         * slow for our needs
         */
        //binpacking(*this, load_l, machine_m, sizes_l);

        /*
         * So naive implementation from Gecode example of bin packing
         */
        // All loads must add up to all item sizes
        linear(*this, load_l, IRT_EQ, totalSize_l);
 
        // Load must be equal to packed items 
        for (int mach_l = 0; mach_l < nbMach_l; ++mach_l)
            linear(*this, sizes_l, x_l.row(mach_l), IRT_EQ, load_l[mach_l]);
    }

    /*
     * Conflict
     */
    int nbServ_l = pContext_p->getNbServices();
    for (int serv_l = 0; serv_l < nbServ_l; ++serv_l) {
        ServiceBO *pServ_l = pContext_p->getService(serv_l);
        typedef unordered_set<int> IntSet;
        IntSet s_l = pServ_l->getProcesses();
        IntVarArgs machine_l;

        for (IntSet::const_iterator it_l = s_l.begin(); it_l != s_l.end(); ++it_l)
            machine_l << machine_m[*it_l];

        distinct(*this, machine_l);
    }

    /*
     * Spread
     */
    // Quentin, c'est a toi !

    /*
     * Depedency
     */
    // TODO

    /*
     * Transient
     */
    for (int res_l = 0; res_l < pContext_p->getNbRessources(); ++res_l) {
        RessourceBO *pRes_l = pContext_p->getRessource(res_l);
        if (! pRes_l->isTransient())
            continue;

        /*
         * Inspired by the naive imprementation of bin packing in Gecode example
         */
 
        // Load must be equal to packed items
        IntVarArgs load_l(*this, nbMach_l, 0, Int::Limits::max);
 
        for (int mach_l = 0; mach_l < nbMach_l; ++mach_l) {
            MachineBO *pMach_l = pContext_p->getMachine(mach_l);
            int capa_l = pMach_l->getCapa(res_l);
            IntArgs sizes_l;
            BoolVarArgs otherProc_l;
            int unremovableCapa_l = 0;
            std::vector<int> solInit_l = pContext_p->getSolInit();

            for (int proc_l = 0; proc_l < nbProc_l; ++proc_l) {
                ProcessBO *pProc_l = pContext_p->getProcess(proc_l);
                int req_l = pProc_l->getRequirement(res_l);
                if (solInit_l[proc_l] == mach_l)
                    unremovableCapa_l += req_l;
                else {
                    otherProc_l << x_l(proc_l, mach_l);
                    sizes_l << req_l;
                }
            }

            // the capacity is decreased by the capacity used by preassigned
            // processus
            rel(*this, load_l[mach_l], IRT_LQ, capa_l - unremovableCapa_l);

            // only the processus not on the machine on the initial solution use
            // capacity
            linear(*this, sizes_l, otherProc_l, IRT_EQ, load_l[mach_l]);
        }
    }

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

#endif //USE_GECODE
