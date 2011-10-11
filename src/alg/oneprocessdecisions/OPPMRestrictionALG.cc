#include "OPPMRestrictionALG.hh"

#include "tools/Log.hh"

OPPMRestrictionALG::OPPMRestrictionALG( ProcessId target_p,
                                        MachinePool const & subset_p)
: target_m(target_p), pool_m()
{
    pool_m = RestrictedMachinePool(subset_p.begin(),subset_p.end());
}

OPPMRestrictionALG::~OPPMRestrictionALG() 
{
}

void OPPMRestrictionALG::filter(ProcessPool &) const
{
    return;
}

void OPPMRestrictionALG::filter( ProcessId const & process_p,
                                 MachinePool & allowAssignment_p) const
{
    if( process_p == target_m)
    {
        LOG(WTF) << "On restreint pour le process " << process_p << std::endl;
        // A refaire : il existe un algo plus rapide si les listes sont triees
        MachinePool::iterator it_l = allowAssignment_p.begin();
        while (it_l != allowAssignment_p.end())
        {
            if ( pool_m.find(*it_l) == pool_m.end() )
            {
                it_l = allowAssignment_p.erase(it_l);
            }
            else
            {
                ++it_l;
            }
        }
    }
    else
    {
        return;
    }
}
