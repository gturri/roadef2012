#include "alg/printDebug/PrintDebugStrategy.hh"
#include "tools/Checker.hh"
#include <iostream>
using namespace std;

ContextALG PrintDebugStrategy::run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p, const variables_map& opt_p){
    Checker checker(&contextAlg_p);


    clog << "*** Traces de PrintDebugStrategy ***" << endl;
    if ( ! checker.isValid() ){
        clog << "La solution n'est pas valide" << endl;
        return contextAlg_p;
    }

    clog << "\tLoad cost : " << checker.computeLoadCost() << endl
        << "\tBalance cost : " << checker.computeBalanceCost() << endl
        << "\tPMC : " << checker.computePMC() << endl
        << "\tSMC : " << checker.computeSMC() << endl
        << "\tMMC : " << checker.computeMMC() << endl
        << "Total : " << checker.computeScore() << endl;

    return contextAlg_p;
}

