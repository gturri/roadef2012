#include "MonteCarloSimulationALG.hh"

#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

int MonteCarloSimulationALG::roll_die(int maxRange_p) 
{
    boost::uniform_int<> dist(0, std::max(0,maxRange_p-1));
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen_m, dist);
    return die();
}


MonteCarloSimulationALG::MonteCarloSimulationALG()
{
}

MonteCarloSimulationALG::~MonteCarloSimulationALG()
{
}

void MonteCarloSimulationALG::run(SolutionALG * pSolution_p)
{
    // remplir la solution actuellement vide
    // -> passer le contexte aussi?
    // -> donner une solution sans affectation?
}
