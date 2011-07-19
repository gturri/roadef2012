#ifndef STRATEGYGENERATIONSELECTER_HH
#define STRATEGYGENERATIONSELECTER_HH
#include <string>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;

class StrategyGeneration;

class StrategyGenerationSelecter {
    public:
        static shared_ptr<StrategyGeneration> getStrategy(const string& strategy_p);
};


#endif
