#include "generateur/alg/StrategyGeneration.hh"
#include "generateur/ParseCmdLine.hh"
#include "generateur/StrategyGenerationSelecter.hh"
#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterInterface.hh"
#include "dtoout/SolutionDtoout.hh"
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
        variables_map args_l = ParseCmdLine::parse(argc, argv);
        shared_ptr<StrategyGeneration> pStrategy_l = StrategyGenerationSelecter::getStrategy(args_l["strategy"].as<string>());
        list<shared_ptr<ContextBO> > instances_l = pStrategy_l->generate(args_l);

        shared_ptr<InstanceWriterInterface> writer_l = WriterSelecter::getWriter(args_l["writer"].as<string>());

        BOOST_FOREACH(shared_ptr<ContextBO> instance_l, instances_l){
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
