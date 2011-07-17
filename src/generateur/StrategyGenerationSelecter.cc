#include "generateur/StrategyGenerationSelecter.hh"
#include "generateur/alg/DummyStrategyGeneration.hh"
#include "generateur/alg/GenerateFromExisting.hh"

shared_ptr<StrategyGeneration> StrategyGenerationSelecter::getStrategy(const string& strategy_p){
    shared_ptr<StrategyGeneration> result_l(new DummyStrategyGeneration);

    if ( strategy_p == "existing" ){
        result_l = shared_ptr<StrategyGeneration>(new GenerateFromExisting);
    }

    return result_l;
}
