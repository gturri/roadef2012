#include "OPPMSpaceALG.hh"

#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include <list>


OPPMSpaceALG::OPPMSpaceALG()
{
}

OPPMSpaceALG::~OPPMSpaceALG()
{
}
 
OPPMSpaceALG::DecisionsPool OPPMSpaceALG::generateDecisions() const
{
    ContextBO const * pContext_l = getpContext()->getContextBO();
    
    std::list<int> eligibleProcesses_l;
    int nbProcesses_l = pContext_l->getNbProcesses();
    for(int process_l = 0; process_l<nbProcesses_l; ++process_l)
    {
        eligibleProcesses_l.push_back(process_l);
    }
    
    
    for (DecisionsPool::const_iterator it_l = decisions_m.begin();
                                       it_l != decisions_m.end();
                                       ++it_l)
    {
        
    }
    
    return DecisionsPool();
}
