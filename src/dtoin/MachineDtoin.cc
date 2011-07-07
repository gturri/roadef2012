#include "dtoin/MachineDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/MMCBO.hh"
#include <tr1/unordered_map>
#include <string>
using namespace std::tr1;

MachineDtoin::MachineDtoin() : alreadyUsed_m (false)
{}

void MachineDtoin::read(ifstream& ifs_p, ContextBO* pContextBO_p){
    //On s'assure que cette instance n'est pas usagee
    if ( alreadyUsed_m ){
        throw string("Un MachineDtoin est utilise deux fois !");
    }
    alreadyUsed_m = true;

    //Lecture sequentielle des machines
    pContext_m = pContextBO_p;
    int nbMachines_l;
    ifs_p >> nbMachines_l;
    mmcCosts_m = vector<vector<int> >(nbMachines_l, vector<int>(nbMachines_l, 0));

    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        int idxNeighborhood_l, idxLocation_l;
        ifs_p >> idxNeighborhood_l >> idxLocation_l;

        NeighborhoodBO* const neigh_l = getNeighborhood(idxNeighborhood_l);
        LocationBO* const loc_l = getLocation(idxLocation_l);
        const vector<int> capas_l = readQteRess(ifs_p);
        const vector<int> safetyCapas_l = readQteRess(ifs_p);

        //Creation de la machine et insertion dans le contexte
        pContext_m->addMachine(new MachineBO(idxMachine_l, loc_l, neigh_l, capas_l, safetyCapas_l));
        readMMCForOneMachine(ifs_p, idxMachine_l);
    }

    sendMMC();
    sendLocations();
    sendNeighborhoods();
}

vector<int> MachineDtoin::readQteRess(ifstream& ifs_p){
    int nbRess_l = pContext_m->getNbRessources();
    vector<int> result_l(nbRess_l);
    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        ifs_p >> result_l[idxRess_l];
    }
    return result_l;
}

LocationBO* MachineDtoin::getLocation(int idx_p){
    for ( int idx_l=pLoc_m.size() ; idx_l <= idx_p ; idx_l++ ){
        pLoc_m.push_back(new LocationBO(idx_l));
    }
    return pLoc_m[idx_p];
}

NeighborhoodBO* MachineDtoin::getNeighborhood(int idx_p){
    for ( int idx_l=pNeigh_m.size() ; idx_l <= idx_p ; idx_l++ ){
        pNeigh_m.push_back(new NeighborhoodBO(idx_l));
    }
    return pNeigh_m[idx_p];
}

void MachineDtoin::readMMCForOneMachine(ifstream& ifs_p, int idxCurMachine_p){
    int nbMachines_l = mmcCosts_m.size();
    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        ifs_p >> mmcCosts_m[idxCurMachine_p][idxMachine_l];
    }
}

void MachineDtoin::sendMMC() const{
    pContext_m->setMMCBO(new MMCBO(mmcCosts_m));
}

void MachineDtoin::sendLocations() const{
    for ( vector<LocationBO*>::const_iterator it_l = pLoc_m.begin() ; it_l != pLoc_m.end() ; it_l++ ){
        pContext_m->addLocation(*it_l);
    }
}

void MachineDtoin::sendNeighborhoods() const{
    for ( vector<NeighborhoodBO*>::const_iterator it_l = pNeigh_m.begin() ; it_l != pNeigh_m.end() ; it_l++ ){
        pContext_m->addNeighborhood(*it_l);
    }

}
