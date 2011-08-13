#ifndef MONTECARLOSIMULATIONALG_HH
#define MONTECARLOSIMULATIONALG_HH

#include <boost/random/mersenne_twister.hpp>

class SolutionALG;

class MonteCarloSimulationALG
{
    public:
        MonteCarloSimulationALG();
        ~MonteCarloSimulationALG();
        
        void run(SolutionALG *);
        
    private:
        int roll_die(int);
        boost::mt19937 gen_m;
        
};

#endif // MONTECARLOSIMULATIONALG_HH
