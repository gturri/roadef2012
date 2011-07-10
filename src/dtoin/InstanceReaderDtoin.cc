#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/BalanceCostDtoin.hh"
#include "dtoin/MachineDtoin.hh"
#include "dtoin/PoidsDtoin.hh"
#include "dtoin/ProcessDtoin.hh"
#include "dtoin/RessourceDtoin.hh"
#include "dtoin/ServiceDtoin.hh"
#include "tools/Log.hh"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

ContextBO InstanceReaderDtoin::read(const string& instance_filename_p){
    ifstream ifs_l(instance_filename_p.c_str());
    if (! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le fichier d'instance " << instance_filename_p << endl;
        throw oss_l.str();
    }

    ContextBO result_l;

    RessourceDtoin ressDtoin_l;
    ressDtoin_l.read(ifs_l, &result_l);
    MachineDtoin machineDtoin_l;
    machineDtoin_l.read(ifs_l, &result_l);
    ServiceDtoin serviceDtoin_l;
    serviceDtoin_l.read(ifs_l, &result_l);
    ProcessDtoin processDtoin_l;
    processDtoin_l.read(ifs_l, &result_l);
    BalanceCostDtoin balanceCostDtoin_l;
    balanceCostDtoin_l.read(ifs_l, &result_l);
    PoidsDtoin poidsDtoin_l;
    poidsDtoin_l.read(ifs_l, &result_l);

    LOG(INFO) << "Fin de la lecture du fichier d'instance" << endl;
    return result_l;
}
