#include "alg/SequenceStrategyOptim.hh"
#include "alg/ContextALG.hh"
#include <boost/foreach.hpp>

SequenceStrategyOptim::~SequenceStrategyOptim(){
    BOOST_FOREACH(StrategyOptim* pStrat_l, sequence_m){
        delete pStrat_l;
    }
}

ContextALG SequenceStrategyOptim::run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p){
    BOOST_FOREACH(StrategyOptim* pStrat_l, sequence_m){
        contextAlg_p = pStrat_l->run(contextAlg_p, heureFinMaxPreconisee_p);
    }
    return contextAlg_p;
}
