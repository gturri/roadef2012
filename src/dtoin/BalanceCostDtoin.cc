#include "dtoin/BalanceCostDtoin.hh"
#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"

void BalanceCostDtoin::read(istream& ifs_p, ContextBO* pContextBO_p){
    int nbBalanceCosts_l;
    ifs_p >> nbBalanceCosts_l;

    for ( int idxBC_l=0 ; idxBC_l < nbBalanceCosts_l ; idxBC_l++ ){
        int idxRess1_l, idxRess2_l, target_l, poids_l;
        ifs_p >> idxRess1_l >> idxRess2_l >> target_l >> poids_l;

        pContextBO_p->addBalanceCost(new BalanceCostBO(
                    pContextBO_p->getRessource(idxRess1_l),
                    pContextBO_p->getRessource(idxRess2_l),
                    target_l,
                    poids_l));
    }

}
