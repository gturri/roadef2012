#ifndef STRATEGYGENERATIONSELECTER_HH
#define STRATEGYGENERATIONSELECTER_HH
#include <string>
#include <memory>
using namespace std;

class StrategyGeneration;

class StrategyGenerationSelecter {
    public:
        static shared_ptr<StrategyGeneration> getStrategy(const string& strategy_p);
};


#endif
