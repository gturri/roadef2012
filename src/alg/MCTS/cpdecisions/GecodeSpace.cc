#ifdef USE_GECODE

#include "GecodeSpace.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "tools/Log.hh"

#include <gecode/minimodel.hh>

using namespace Gecode;
typedef std::vector<int> Solution;

GecodeSpace::GecodeSpace(const ContextBO *pContext_p, const vector<int> &perm_p) :
    machine_m(*this, pContext_p->getNbProcesses(),
              0, pContext_p->getNbMachines() - 1),
    nbUnmovedProcs_m(*this, 0, pContext_p->getNbProcesses()),
    bMatrix_m(*this, pContext_p->getNbProcesses() * pContext_p->getNbMachines(),
              0, 1)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();
    const Solution &solInit_l = pContext_p->getSolInit();

    // nbUnmovedProcs_m
    IntArgs solInitArgs_l(nbProc_l);
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        solInitArgs_l[perm_p[proc_l]] = solInit_l[proc_l];
    count(*this, machine_m, solInitArgs_l, IRT_EQ, nbUnmovedProcs_m);
    // on veut pas la solution initiale
    rel(*this, nbUnmovedProcs_m, IRT_NQ, nbProc_l);

    // matrix proc x mach
    Matrix<BoolVarArgs> x_l(bMatrix_m, nbProc_l, nbMach_l);
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        channel(*this, x_l.col(proc_l), machine_m[proc_l]);

    capacity(pContext_p, perm_p, x_l);
    conflict(pContext_p, perm_p);
    spread(pContext_p, perm_p);
    dependency(pContext_p, perm_p);
    transient(pContext_p, perm_p, x_l);

    // random branching to do a Monte Carlo generation
    // celui-la est pas top random... faut le randomiser.
    branch(*this, nbUnmovedProcs_m, INT_VAL_MAX);
    branch(*this, machine_m,
           tiebreak(INT_VAR_AFC_MAX, INT_VAR_SIZE_MIN),
           INT_VAL_RND);
    // celui-la tout seul est bien random, mais ca marche pas encore assez bien
    // pour le moment (correct pour a1_1)
    //branch(*this, machine_m, INT_VAR_NONE, INT_VAL_RND);
}

GecodeSpace::GecodeSpace(bool share_p, GecodeSpace &that) :
    Space(share_p, that)
{
    machine_m.update(*this, share_p, that.machine_m);
    nbUnmovedProcs_m.update(*this, share_p, that.nbUnmovedProcs_m);
    bMatrix_m.update(*this, share_p, that.bMatrix_m);
}

Gecode::Space *GecodeSpace::copy(bool share_p)
{
    return new GecodeSpace(share_p, *this);
}

std::vector<int> GecodeSpace::solution(const vector<int> &perm_p)
{
    assert(status() == SS_SOLVED && machine_m.assigned());
    assert((int) perm_p.size() == machine_m.size());
    std::vector<int> res_l(perm_p.size());

    for (size_t proc_l = 0; proc_l < perm_p.size(); ++proc_l)
        res_l[proc_l] = machine_m[perm_p[proc_l]].val();

    return res_l;
}

/*
 * Constraints
 */
void GecodeSpace::capacity(const ContextBO *pContext_p, const vector<int> &perm_p, Matrix<BoolVarArgs> &x_p)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();
    int nbRes_l = pContext_p->getNbRessources();

    for (int res_l = 0; res_l < nbRes_l; ++res_l) {
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
            sizes_l[perm_p[proc_l]] = req_l;
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
            linear(*this, sizes_l, x_p.row(mach_l), IRT_EQ, load_l[mach_l]);
    }

    // we do an agregated resource on each machine to combine knowledge
    IntVarArgs load_l(*this, nbMach_l, 0, Int::Limits::max);
    for (int mach_l = 0; mach_l < nbMach_l; ++mach_l) {
        MachineBO *pMach_l = pContext_p->getMachine(mach_l);
        int capa_l = 0;
        for (int res_l = 0; res_l < nbRes_l; ++res_l)
            capa_l += pMach_l->getCapa(res_l);
        rel(*this, load_l[mach_l], IRT_LQ, capa_l);
    }

    IntArgs sizes_l(nbProc_l);
    int totalSize_l = 0;
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l) {
        ProcessBO *pProc_l = pContext_p->getProcess(proc_l);
        int machSize_l = 0;

        for (int res_l = 0; res_l < nbRes_l; ++res_l)
            machSize_l += pProc_l->getRequirement(res_l);

        totalSize_l += machSize_l;
        sizes_l[perm_p[proc_l]] = machSize_l;
    }

    linear(*this, load_l, IRT_EQ, totalSize_l);
    for (int mach_l = 0; mach_l < nbMach_l; ++mach_l)
        linear(*this, sizes_l, x_p.row(mach_l), IRT_EQ, load_l[mach_l]);
}

void GecodeSpace::conflict(const ContextBO *pContext_p, const vector<int> &perm_p)
{
    int nbServ_l = pContext_p->getNbServices();

    for (int serv_l = 0; serv_l < nbServ_l; ++serv_l) {
        ServiceBO *pServ_l = pContext_p->getService(serv_l);
        typedef unordered_set<int> IntSet;
        IntSet s_l = pServ_l->getProcesses();
        IntVarArgs machine_l;

        if (s_l.size() < 2)
            continue;

        for (IntSet::const_iterator it_l = s_l.begin(); it_l != s_l.end(); ++it_l)
            machine_l << machine_m[perm_p[*it_l]];

        distinct(*this, machine_l);
    }
}

void GecodeSpace::spread(const ContextBO *pContext_p, const vector<int> &perm_p)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();
    int nbServ_l = pContext_p->getNbServices();
    int nbLoc_l = pContext_p->getNbLocations();

    if (nbLoc_l < 2)
        return;

    // creation of location_l[proc] -> location corresponding to the
    // proc
    IntArgs machToLoc_l;
    for (int mach_l = 0; mach_l < nbMach_l; ++mach_l) {
        MachineBO *pMach_l = pContext_p->getMachine(mach_l);
        machToLoc_l <<  pMach_l->getLocation()->getId();
    }
    IntSharedArray sMachToLoc_l(machToLoc_l);
    IntVarArgs location_l(*this, nbProc_l, 0, nbLoc_l - 1);
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        element(*this, sMachToLoc_l, machine_m[proc_l], location_l[proc_l]);


    for (int serv_l = 0; serv_l < nbServ_l; ++serv_l) {
        ServiceBO *pServ_l = pContext_p->getService(serv_l);
        int spreadMin_l = pServ_l->getSpreadMin();

        if (spreadMin_l < 2)
            continue;

        typedef unordered_set<int> IntSet;
        IntSet s_l = pServ_l->getProcesses();
        IntVarArgs servLoc_l;
        for (IntSet::const_iterator it_l = s_l.begin(); it_l != s_l.end(); ++it_l)
            servLoc_l << location_l[perm_p[*it_l]];

        nvalues(*this, servLoc_l, IRT_GQ,  spreadMin_l);
    }
}

void GecodeSpace::dependency(const ContextBO *pContext_p, const vector<int> &perm_p)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();
    int nbServ_l = pContext_p->getNbServices();
    int nbNeigh_l = pContext_p->getNbNeighborhoods();
 
    // creation of neighborhood_l[proc] -> neighborhood corresponding to the
    // proc
    IntArgs machToNeigh_l;
    for (int mach_l = 0; mach_l < nbMach_l; ++mach_l) {
        MachineBO *pMach_l = pContext_p->getMachine(mach_l);
        machToNeigh_l <<  pMach_l->getNeighborhood()->getId();
    }
    IntSharedArray sMachToNeigh_l(machToNeigh_l);
    IntVarArgs neighborhood_l(*this, nbProc_l, 0, nbNeigh_l - 1);
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        element(*this, sMachToNeigh_l, machine_m[proc_l], neighborhood_l[proc_l]);

    // neighborhoods_l[serv_l] is the set of neighborhoods where we can find
    // serv_l
    SetVarArray neighborhoods_l(*this, nbServ_l,
                                IntSet::empty, IntSet(0, nbNeigh_l - 1));
    for (int serv_l = 0; serv_l < nbServ_l; ++serv_l) {
        ServiceBO *pServ_l = pContext_p->getService(serv_l);
        typedef unordered_set<int> IntSet;
        IntSet s_l = pServ_l->getProcesses();
        IntVarArgs servNeigh_l;
        for (IntSet::const_iterator it_l = s_l.begin(); it_l != s_l.end(); ++it_l)
            servNeigh_l << neighborhood_l[perm_p[*it_l]];

        channel(*this, servNeigh_l, neighborhoods_l[serv_l]);

        // s1 depends on s2 <=> neighborhoods_l[s1] is included in
        // neighborhoods_l[s2]
        IntSet depend_l = pServ_l->getServicesIDependOn();
        for (IntSet::const_iterator it_l = depend_l.begin();
             it_l != depend_l.end(); ++it_l)
            rel(*this, neighborhoods_l[serv_l], SRT_SUB, neighborhoods_l[*it_l]);
    }
}

void GecodeSpace::transient(const ContextBO *pContext_p, const vector<int> &perm_p, Matrix<BoolVarArgs> &x_p)
{
    int nbProc_l = pContext_p->getNbProcesses();
    int nbMach_l = pContext_p->getNbMachines();
    int nbRes_l = pContext_p->getNbRessources();
    const Solution& solInit_l = pContext_p->getSolInit();

    for (int res_l = 0; res_l < nbRes_l; ++res_l) {
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

            for (int proc_l = 0; proc_l < nbProc_l; ++proc_l) {
                ProcessBO *pProc_l = pContext_p->getProcess(proc_l);
                int req_l = pProc_l->getRequirement(res_l);
                if (solInit_l[proc_l] == mach_l)
                    unremovableCapa_l += req_l;
                else {
                    otherProc_l << x_p(perm_p[proc_l], mach_l);
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
}

/*
 * Decision management
 */
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
    for (int i_l = 1; i_l < machine_m.size(); ++i_l)
        if (machine_m[i_l].size() > machine_m[target_l].size())
            target_l = i_l;

    assert(machine_m[target_l].size() > 1);

    // for the moment, simple median branching
    res_l.push_back(new CPDecisionALG(target_l, machine_m[target_l].min(), machine_m[target_l].med()));
    res_l.push_back(new CPDecisionALG(target_l, machine_m[target_l].med() + 1, machine_m[target_l].max()));

    return res_l;
}

/*
 * Local search
 */
void GecodeSpace::restrictNbMove(int nb_p, const vector<int> &sol_p, const vector<int> &perm_p)
{
    assert((int) perm_p.size() == machine_m.size());
    assert((int) sol_p.size() == machine_m.size());
    int nbProc_l = machine_m.size();
    IntArgs solArgs_l(nbProc_l);
    for (int proc_l = 0; proc_l < nbProc_l; ++proc_l)
        solArgs_l[perm_p[proc_l]] = sol_p[proc_l];

    count(*this, machine_m, solArgs_l, IRT_EQ, nbProc_l - nb_p);
}


#endif //USE_GECODE
