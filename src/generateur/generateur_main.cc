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

#include "generateur/alg/StrategyGeneration.hh"
#include "generateur/ParseCmdLineGenerateur.hh"
#include "generateur/StrategyGenerationSelecter.hh"
#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterInterface.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Checker.hh"
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost;
using namespace boost::program_options;
using namespace std;

int main(int argc, char** argv){
    try {
        variables_map args_l = ParseCmdLineGenerateur::parse(argc, argv);
        shared_ptr<StrategyGeneration> pStrategy_l = StrategyGenerationSelecter::getStrategy(args_l["strategy"].as<string>());
        list<shared_ptr<ContextBO> > instances_l = pStrategy_l->generate(args_l);

        shared_ptr<InstanceWriterInterface> writer_l = WriterSelecter::getWriter(args_l["writer"].as<string>());

        BOOST_FOREACH(shared_ptr<ContextBO> instance_l, instances_l){
            assert(check(instance_l.get()));
            static int compteur_l(0);
            compteur_l++;
            ostringstream out_instance_filename_l;
            out_instance_filename_l << args_l["out"].as<string>() << "_inst_" << compteur_l << ".txt";
            writer_l->write(instance_l.get(), out_instance_filename_l.str());

            ostringstream out_sol_filename_l;
            out_sol_filename_l << args_l["out"].as<string>() << "_sol_" << compteur_l << ".txt";
            SolutionDtoout::writeSolInit(instance_l.get(), out_sol_filename_l.str());
        }
    } catch (string& s_l ){
        cerr << "Exception catchee : " << s_l << endl;
    }
}
