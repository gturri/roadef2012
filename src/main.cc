#include "alg/ContextALG.hh"
#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"
#include "alg/StrategySelecter.hh"
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/ParseCmdLine.hh"
#include "tools/Log.hh"
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    variables_map opt_l = ParseCmdLine::parse(argc, argv);
    ParseCmdLine::traitementOptionsSimples(opt_l);

    LOG(INFO) << "temps limite : " << opt_l["time"].as<int>() << " s" << endl
        << "instance file  : ./" << opt_l["param"].as<string>() << endl
        << "original sol : ./" << opt_l["init"].as<string>() << endl
        << "new sol : ./" << opt_l["out"].as<string>() << endl
        << "seed : " << opt_l["seed"].as<int>() << endl;

    try {
        /* Lecture du fichier d'instance et de solution initiale
         */
        cerr << "reading instance" << endl;
        InstanceReaderDtoin reader_l;
        ContextBO contextBO_l = reader_l.read(opt_l["param"].as<string>());
        SolutionDtoin::read(opt_l["init"].as<string>(), &contextBO_l);

        /* Lancement de la sequence d'optim.
         */
        cerr << "creating context" << endl;
        ContextALG contextALG_l(&contextBO_l);
            //Initialise SolutionDtoout::bestSol_m
        contextALG_l.checkCompletAndMajBestSol(contextALG_l.getCurrentSol(), false);
        StrategyOptim* pStrategy_l = StrategySelecter::buildStrategy(opt_l);
        cerr << "running method" << endl;
        pStrategy_l->run(contextALG_l, time(0) + opt_l["time"].as<int>(), opt_l);

        /* Risque de fuite de memoire : si une exception est levee pendant l'optim,
         * on ne deletera jamais cette strategie.
         * (bon, ok, reflexion de puriste n'ayant que peu de consequences pratiques vu le contexte...)
         */
        delete pStrategy_l;

    } catch (string s_l){
        LOG(ERREUR) << "Levee de l'exception : " << s_l << endl;
    }

    return 0;
}





