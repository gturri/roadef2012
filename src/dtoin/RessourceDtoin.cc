#include "dtoin/RessourceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"

void RessourceDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbRess_l;
    is_p >> nbRess_l;

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        bool isTransient_l;
        is_p >> isTransient_l;
        int weightLoadCost_l;
        is_p >> weightLoadCost_l;

        pContextBO_p->addRessource(new RessourceBO(idxRess_l, isTransient_l, weightLoadCost_l));
    }
};
