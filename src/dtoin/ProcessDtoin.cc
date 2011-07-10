#include "dtoin/ProcessDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include <vector>
using namespace std;

void ProcessDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l, nbRessources_l(pContextBO_p->getNbRessources());
    is_p >> nbProcesses_l;

    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxService_l, pmc_l;
        is_p >> idxService_l;
        vector<int> vRequirements_l(nbProcesses_l, 0);

        for ( int idxRess_l=0 ; idxRess_l < nbRessources_l ; idxRess_l++ ){
            is_p >> vRequirements_l[idxRess_l];
        }

        is_p >> pmc_l;

        pContextBO_p->addProcess(new ProcessBO(idxP_l, pContextBO_p->getService(idxService_l), vRequirements_l, pmc_l));
    }
}
