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

SpaceALG * OPPMSpaceALG::clone()
{
    OPPMSpaceALG * pClone_l = new OPPMSpaceALG;
    pClone_l->setpContext(getpContext());
    pClone_l->setpConstraintSystem(pConstraintSystem_m);
    pClone_l->setpEvaluationSystem(pEvaluationSystem_m);
    
    // transmission des decisions, memoire gerer par l'arbre
    for(DecisionsPool::iterator it_l = decisions_m.begin();
                                it_l != decisions_m.end();
                                ++it_l )
    {
        pClone_l->decisions_m.push_back(*it_l);
    }
    return pClone_l;
}
 
OPPMSpaceALG::DecisionsPool OPPMSpaceALG::generateDecisions() const
{
    cerr << "\ton genere les decisions a partir de " << getpContext() << endl;
    
    ContextBO const * pContext_l = getpContext()->getContextBO();
    
    cerr << "\ton liste les process disponibles" << endl; 

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
        cerr << "\tAucun ne l'est, on retourne une liste vide" << endl;
        return DecisionsPool();
    }

    cerr << "\tOn en a trouve " << eligibleProcesses_l.size() << endl; 

    int target_l  = eligibleProcesses_l.front();
    int nbBuckets_l = 3;
    
    cerr << "\tOn reparti en " << nbBuckets_l << endl;
    typedef vector<OPPMDecisionALG *> LocalDecisionPool;
    LocalDecisionPool decisons_l;
    vector< OPPMDecisionALG::MachinePool > buckets_l;
    for (int idx_l = 0; idx_l < nbBuckets_l; ++idx_l)
    {
        decisons_l.push_back(new OPPMDecisionALG);
        buckets_l.push_back(OPPMDecisionALG::MachinePool());
    }
    
    cerr << "\tOn replit les buckets" << endl;
    int nbMachines_l = pContext_l->getNbMachines();
    for (int machine_l = 0; machine_l < nbMachines_l; ++machine_l)
    {
        int idx_l = machine_l % nbBuckets_l;
        buckets_l[idx_l].push_back(machine_l);
    }
    
    cerr << "\tOn cree les decision" << endl;
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
