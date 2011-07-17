#include "dtoin/RessourceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "tools/Log.hh"
#include <cassert>

void RessourceDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbRess_l;
    is_p >> nbRess_l;
    LOG(DEBUG) << nbRess_l << " ressources" << endl;
    assert(nbRess_l > 0);

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        bool isTransient_l;
        is_p >> isTransient_l;
        int weightLoadCost_l;
        is_p >> weightLoadCost_l;
        LOG(DEBUG) << "\tRessource " << idxRess_l << " : isTransient=" << isTransient_l << ", poids=" << weightLoadCost_l << endl;

        pContextBO_p->addRessource(new RessourceBO(idxRess_l, isTransient_l, weightLoadCost_l));
    }
};
