#include "generateur/alg/StrategyGeneration.hh"
#include "generateur/ParseCmdLine.hh"
#include <iostream>
#include <boost/program_options.hpp>
using namespace boost::program_options;
using namespace std;

int main(int argc, char** argv){
    cout << "test" << endl;
    variables_map args_l = ParseCmdLine::parse(argc, argv);
}
