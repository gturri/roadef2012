#include "generateur/alg/StrategyGeneration.hh"
#include "generateur/ParseCmdLine.hh"
#include "generateur/StrategyGenerationSelecter.hh"
#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterInterface.hh"
#include <iostream>
#include <memory>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
using namespace boost::program_options;
using namespace std;

int main(int argc, char** argv){
    variables_map args_l = ParseCmdLine::parse(argc, argv);
    shared_ptr<StrategyGeneration> pStrategy_l = StrategyGenerationSelecter::getStrategy(args_l["strategy"].as<string>());
    list<shared_ptr<ContextBO> > instances_l = pStrategy_l->generate(args_l);

    shared_ptr<InstanceWriterInterface> writer_l = WriterSelecter::getWriter(args_l["writer"].as<string>());

    BOOST_FOREACH(shared_ptr<ContextBO> instance_l, instances_l){
        writer_l->write(instance_l.get(), "dummyInstance.txt");
    }
}
