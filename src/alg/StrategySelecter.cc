#include "alg/StrategySelecter.hh"
#include "alg/StrategyOptim.hh"
#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"

StrategyOptim* StrategySelecter::buildStrategy(const variables_map& opt_p){
    string strategyName_l;
    if ( opt_p.count("strategy") ){
        strategyName_l = opt_p["strategy"].as<string>();
    }

    /* Ajouter ici une ribambelle de "if(strategyName_l == myName) return new myStrategy;
     */

    //Cas par defaut (ou : lever une exception ?)
    return new DummyStrategyOptim();
}
