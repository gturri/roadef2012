#include "OPPMSpaceALG.hh"
#include "OPPMDecisionALG.hh"

#include "alg/ContextALG.hh"
#include "alg/DecisionALG.hh"
#include "bo/ContextBO.hh"
#include <list>

#include <iostream>
using namespace std;

OPPMSpaceALG::OPPMSpaceALG()
{
}

OPPMSpaceALG::~OPPMSpaceALG()
{
}
 
OPPMSpaceALG::DecisionsPool OPPMSpaceALG::generateDecisions() const
{
    cerr << "on genere les solutions" << endl;
    
    ContextBO const * pContext_l = getpContext()->getContextBO();
    
    cerr << "on liste les process disponible" << endl; 

    std::list<int> eligibleProcesses_l;
    int nbProcesses_l = pContext_l->getNbProcesses();
    for(int process_l = 0; process_l<nbProcesses_l; ++process_l)
    {
        bool dontAppearInDecisions_l = true;
        for (DecisionsPool::const_iterator it_l = decisions_m.begin();
                                           it_l != decisions_m.end();
                                           ++it_l)
        {
            if ( (*it_l)->workOnProcess(process_l))
            {
                dontAppearInDecisions_l = false;
            }
        }
        if (dontAppearInDecisions_l)
        {
            eligibleProcesses_l.push_back(process_l);
        }
    }

    if (eligibleProcesses_l.size() == 0)
    {
        cerr << "Aucun ne l'est, on retourne une liste vide" << endl;
        return DecisionsPool();
    }

    cerr << "On en a trouve " << eligibleProcesses_l.size() << endl; 

    int target_l  = eligibleProcesses_l.front();
    int nbBuckets_l = 3;
    typedef vector<OPPMDecisionALG *> LocalDecisionPool;
    LocalDecisionPool decisons_l;
    vector< OPPMDecisionALG::MachinePool > buckets_l;
    for (int idx_l = 0; idx_l < nbBuckets_l; ++idx_l)
    {
        decisons_l[idx_l] = new OPPMDecisionALG;
        buckets_l.push_back(OPPMDecisionALG::MachinePool());
    }
    int nbMachines_l = pContext_l->getNbMachines();
    for (int machine_l = 0; machine_l < nbMachines_l; ++machine_l)
    {
        int idx_l = machine_l % nbBuckets_l;
        buckets_l[idx_l].push_back(machine_l);
    }
    DecisionsPool returnedDecisions_l;
    for(int idx_l = 0; idx_l < nbBuckets_l; ++idx_l)
    {
        OPPMDecisionALG * pDecisions_l = decisons_l[idx_l];
        pDecisions_l->setRestrictedSubset(buckets_l[idx_l]);
        pDecisions_l->setTarget(target_l);
        returnedDecisions_l.push_back(pDecisions_l);
    }

    return returnedDecisions_l;
}
