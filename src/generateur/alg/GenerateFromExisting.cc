#include "generateur/alg/GenerateFromExisting.hh"
#include "dtoin/InstanceReaderInterface.hh"
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

list<shared_ptr<ContextBO> > GenerateFromExisting::generate(const variables_map& args_p){
    shared_ptr<InstanceReaderInterface> pReader_l = getReader(args_p);
    string inFilename_l = args_p["fromExistingInst"].as<string>();
    list<shared_ptr<ContextBO> > result_l;
    ContextBO contextInit_l = pReader_l->read(inFilename_l);

    if ( ! args_p.count("fromExistingSol") ){
        ostringstream oss_l;
        oss_l << "Strategie de generation demandee : \"From existing\", mais pas desolution initiale fourni. Utiliser l'option --fromExistingSol nomFichier" << endl;
        throw oss_l.str();
    }

    SolutionDtoin::read(args_p["fromExistingSol"].as<string>(), &contextInit_l);

    result_l.push_back(shared_ptr<ContextBO>(new ContextBO(contextInit_l)));
    return result_l;
}

shared_ptr<InstanceReaderInterface> GenerateFromExisting::getReader(const variables_map& args_p){
    if ( ! args_p.count("fromExistingInst") ){
        ostringstream oss_l;
        oss_l << "Strategie de generation demandee : \"From existing\", mais pas d'instance initiale fournie. Utiliser l'option --fromExistingInst nomFichier" << endl;
        throw oss_l.str();
    }

    string filename_l = args_p["fromExistingInst"].as<string>();
    ifstream ifs_l(filename_l);
    if ( ! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvir le fichier d'instance " << filename_l <<endl;
        throw oss_l.str();
    }

    //TODO : lorsqu'il y aura d'autres type de readers, ajouter des tests pour caracteriser le flux d'entree
    shared_ptr<InstanceReaderInterface> result_l(new InstanceReaderDtoin);
    return result_l;
}
