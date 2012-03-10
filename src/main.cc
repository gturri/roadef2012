/*
 * Copyright (c) 2011 Pierre-Etienne Bougué <pe.bougue(a)gmail.com>
 * Copyright (c) 2011 Florian Colin <florian.colin28(a)gmail.com>
 * Copyright (c) 2011 Kamal Fadlaoui <kamal.fadlaoui(a)gmail.com>
 * Copyright (c) 2011 Quentin Lequy <quentin.lequy(a)gmail.com>
 * Copyright (c) 2011 Guillaume Pinot <guillaume.pinot(a)tremplin-utc.net>
 * Copyright (c) 2011 Cédric Royer <cedroyer(a)gmail.com>
 * Copyright (c) 2011 Guillaume Turri <guillaume.turri(a)gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "alg/ContextALG.hh"
#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"
#include "alg/StrategySelecter.hh"
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/ParseCmdLine.hh"
#include "tools/Log.hh"
#include <boost/thread.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
using namespace boost;

struct Run {
  void operator()(const variables_map& opt_p){
    LOG(INFO) << "temps limite : " << opt_p["time"].as<int>() << " s" << endl
      << "instance file  : ./" << opt_p["param"].as<string>() << endl
      << "original sol : ./" << opt_p["init"].as<string>() << endl
      << "new sol : ./" << opt_p["out"].as<string>() << endl
      << "seed : " << opt_p["seed"].as<int>() << endl;

    try {
      /* Lecture du fichier d'instance et de solution initiale
      */
      LOG(INFO) << "reading instance" << endl;
      InstanceReaderDtoin reader_l;
      ContextBO contextBO_l = reader_l.read(opt_p["param"].as<string>());
      SolutionDtoin::read(opt_p["init"].as<string>(), &contextBO_l);

      /* Lancement de la sequence d'optim.
      */
      LOG(INFO) << "creating context" << endl;
      ContextALG contextALG_l(&contextBO_l);
      //Initialise SolutionDtoout::bestSol_m
      contextALG_l.checkCompletAndMajBestSol(contextALG_l.getCurrentSol(), false);
      StrategyOptim* pStrategy_l = StrategySelecter::buildStrategy(opt_p);
      LOG(INFO) << "running method" << endl;
      pStrategy_l->run(contextALG_l, time(0) + opt_p["time"].as<int>(), opt_p);

      /* Risque de fuite de memoire : si une exception est levee pendant l'optim,
       * on ne deletera jamais cette strategie.
       * (bon, ok, reflexion de puriste n'ayant que peu de consequences pratiques vu le contexte...)
       */
      delete pStrategy_l;

    } catch (string s_l){
      LOG(ERREUR) << "Levee de l'exception : " << s_l << endl;
    }

  }
};

int main(int argc, char **argv) {
    variables_map opt_l = ParseCmdLine::parse(argc, argv);
    ParseCmdLine::traitementOptionsSimples(opt_l);

    Run run_l;
    thread thread_l(run_l, opt_l);
    if ( thread_l.timed_join(posix_time::seconds(opt_l["time"].as<int>())) ){
      LOG(INFO) << "Run killed because time limit has been reached" << endl;
    }


    return 0;
}





