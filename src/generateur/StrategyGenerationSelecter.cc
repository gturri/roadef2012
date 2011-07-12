#include "generateur/StrategyGenerationSelecter.hh"
#include "generateur/alg/DummyStrategyGeneration.hh"

shared_ptr<StrategyGeneration> StrategyGenerationSelecter::getStrategy(const string& strategy_p){
    shared_ptr<StrategyGeneration> result_l(new DummyStrategyGeneration());
    return result_l;
}
