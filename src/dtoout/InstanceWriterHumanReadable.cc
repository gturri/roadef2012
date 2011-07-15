#include "dtoout/InstanceWriterHumanReadable.hh"
#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <boost/foreach.hpp>
#include <sstream>
using namespace std;

string InstanceWriterHumanReadable::writeOnString(ContextBO const * pContextBO_p){
    ostringstream oss_l;

    oss_l << writeMajorTitle("Instance") << endl
        << writeRessources(pContextBO_p)
        << writeMachines(pContextBO_p)
        << writeServices(pContextBO_p)
        << writeProcesses(pContextBO_p)
        << writeBalanceCost(pContextBO_p)
        << writePoids(pContextBO_p);
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeRessources(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeSectionTitle("Ressources") << endl;
    int nbRess_l = pContextBO_p->getNbRessources();
    
    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        RessourceBO* pRess_l = pContextBO_p->getRessource(idxRess_l);
        oss_l << endl
            << writeSubTitle("Ressource", idxRess_l, nbRess_l) << endl
            << writeCarac("isTransient", pRess_l->isTransient()) << endl
            << writeCarac("weightLoadCost", pRess_l->getWeightLoadCost()) << endl;
    }

    oss_l << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeMachines(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeSectionTitle("Machines") << endl;
    int nbMachines_l = pContextBO_p->getNbMachines();
    
    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        MachineBO* pMachine_l = pContextBO_p->getMachine(idxMachine_l);
        oss_l << endl
            << writeSubTitle("Machine", idxMachine_l, nbMachines_l) << endl
            << writeCarac("Neighborhood", pMachine_l->getNeighborhood()->getId()) << endl
            << writeCarac("Location", pMachine_l->getLocation()->getId()) << endl
            << writeListOfCaracs("Capa", pMachine_l->getCapas()) << endl
            << writeListOfCaracs("SafetyCapa", pMachine_l->getSafetyCapas()) << endl
            << writeListOfCaracs("MMC", pContextBO_p->getMMCBO()->getCosts(pMachine_l)) << endl;
    }

    oss_l << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeServices(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeSectionTitle("Services") << endl;
    int nbServices_l = pContextBO_p->getNbServices();

    for ( int idxService_l=0 ; idxService_l < nbServices_l ; idxService_l++ ){
        ServiceBO* pService_l = pContextBO_p->getService(idxService_l);
        oss_l << endl
            << writeSubTitle("Service", idxService_l, nbServices_l) << endl
            << writeCarac("SpreadMin", pService_l->getSpreadMin()) << endl
            << writeListOfCaracs("Dependances", pService_l->getServicesIDependOn()) << endl;
    }

    oss_l << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeProcesses(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeSectionTitle("Processes") << endl;
    int nbProcesses_l = pContextBO_p->getNbProcesses();

    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        ProcessBO* pProcess_l = pContextBO_p->getProcess(idxP_l);
        oss_l << endl
            << writeSubTitle("Process", idxP_l, nbProcesses_l) << endl
            << writeCarac("Service", pProcess_l->getService()->getId()) << endl
            << writeListOfCaracs("RessourcesRequises", pProcess_l->getRequirements()) << endl
            << writeCarac("PMC", pProcess_l->getPMC()) << endl;
    }

    oss_l << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeBalanceCost(ContextBO const * pContextBO_p){
    ostringstream  oss_l;
    oss_l << writeSectionTitle("BalanceCost") << endl;
    int nbBC_l = pContextBO_p->getNbBalanceCosts();

    for ( int idxBC_l=0 ; idxBC_l < nbBC_l ; idxBC_l++ ){
        BalanceCostBO* pBC_l = pContextBO_p->getBalanceCost(idxBC_l);
        oss_l << endl
            << writeSubTitle("BalanceCost", idxBC_l, nbBC_l) << endl
            << writeCarac("Ress1", pBC_l->getRessource1()->getId()) << endl
            << writeCarac("Ress2", pBC_l->getRessource2()->getId()) << endl
            << writeCarac("Target", pBC_l->getTarget()) << endl
            << writeCarac("Poids", pBC_l->getPoids()) << endl; 
    }

    oss_l << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writePoids(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeSectionTitle("Poids") << endl
        << writeCarac("PMC", pContextBO_p->getPoidsPMC()) << endl
        << writeCarac("SMC", pContextBO_p->getPoidsSMC()) << endl
        << writeCarac("MMC", pContextBO_p->getPoidsMMC()) << endl
        << endl;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeTitle(const string& titre_p, int level_p){
    ostringstream oss_l;
    for ( int idx_l=0 ; idx_l < level_p ; idx_l++ ){
        oss_l << "=";
    }
    ostringstream result_l;
    result_l << oss_l.str() << " " << titre_p << " " << oss_l.str();
    return result_l.str();
}

string InstanceWriterHumanReadable::writeSubTitle(const string& typeEntite_p, int idx_p, int nbTotal_p){
    ostringstream oss_l;
    oss_l << typeEntite_p << " " << idx_p << " / " << nbTotal_p;
    return writeTitle(oss_l.str(), 4);
}

string InstanceWriterHumanReadable::writeCarac(const string& caracName_p, int carac_p){
    ostringstream oss_l;
    oss_l << "  * " << caracName_p << " : " << carac_p;
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeListOfCaracs(const string& caracsName_p, const vector<int>& caracs_p){
    ostringstream oss_l;
    oss_l << "  * " << caracsName_p << " :";
    BOOST_FOREACH(int carac_l, caracs_p){
        oss_l << " " << carac_l;
    }
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeListOfCaracs(const string& caracsName_p, const unordered_set<int>& caracs_p){
    //FIXME : duplication de code avec la methode eponyme...
    ostringstream oss_l;
    oss_l << "  * " << caracsName_p << " :";
    BOOST_FOREACH(int carac_l, caracs_p){
        oss_l << " " << carac_l;
    }
    return oss_l.str();
}

string InstanceWriterHumanReadable::writeMajorTitle(const string& title_p){
    return writeTitle(title_p, 6);
}

string InstanceWriterHumanReadable::writeSectionTitle(const string& title_p){
    return writeTitle(title_p, 5);
}
