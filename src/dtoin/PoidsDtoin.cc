#include "dtoin/PoidsDtoin.hh"
#include "bo/ContextBO.hh"
#include "tools/Log.hh"

void PoidsDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int poidsPMC_l, poidsSMC_l, poidsMMC_l;
    is_p >> poidsPMC_l >> poidsSMC_l >> poidsMMC_l;
    LOG(DEBUG) << "poids PMC=" << poidsPMC_l << ", poids SMC=" << poidsSMC_l << ", poids MMC=" << poidsMMC_l << endl;


    pContextBO_p->setPoidsPMC(poidsPMC_l);
    pContextBO_p->setPoidsSMC(poidsSMC_l);
    pContextBO_p->setPoidsMMC(poidsMMC_l);
}
