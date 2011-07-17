#include "dtoin/BalanceCostDtoin.hh"
#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "tools/Log.hh"
#include <cassert>

void BalanceCostDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbBalanceCosts_l;
    is_p >> nbBalanceCosts_l;
    LOG(DEBUG) << nbBalanceCosts_l << " balance costs" << endl;
    assert(nbBalanceCosts_l >= 0);

    for ( int idxBC_l=0 ; idxBC_l < nbBalanceCosts_l ; idxBC_l++ ){
        int idxRess1_l, idxRess2_l, target_l, poids_l;
        is_p >> idxRess1_l >> idxRess2_l >> target_l >> poids_l;
        LOG(DEBUG) << "\tBC " << idxBC_l << " : r1=" << idxRess1_l << ", r2=" << idxRess2_l << ", target=" << target_l << ", poids=" << poids_l << endl;


        pContextBO_p->addBalanceCost(new BalanceCostBO(
                    pContextBO_p->getRessource(idxRess1_l),
                    pContextBO_p->getRessource(idxRess2_l),
                    target_l,
                    poids_l));
    }

}
