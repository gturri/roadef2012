#include "alg/StrategySelecter.hh"
#include "alg/StrategyOptim.hh"
#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"

StrategyOptim* StrategySelecter::buildStrategy(const variables_map& opt_l){
    return new DummyStrategyOptim();
}
