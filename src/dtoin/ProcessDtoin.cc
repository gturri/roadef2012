#include "dtoin/ProcessDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "tools/Log.hh"
#include <cassert>
#include <vector>
using namespace std;

void ProcessDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l, nbRessources_l(pContextBO_p->getNbRessources());
    is_p >> nbProcesses_l;
    LOG(DEBUG) << nbProcesses_l << " processes" << endl;
    assert(nbProcesses_l > 0);


    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxService_l, pmc_l;
        is_p >> idxService_l;
        assert(idxService_l >= 0);
        vector<int> vRequirements_l(nbProcesses_l, 0);

        for ( int idxRess_l=0 ; idxRess_l < nbRessources_l ; idxRess_l++ ){
            is_p >> vRequirements_l[idxRess_l];
        }

        is_p >> pmc_l;
        LOG(DEBUG) << "\tLe process " << idxP_l << " est dans le service " << idxService_l << " et a un pmc de " << pmc_l << endl;

        pContextBO_p->addProcess(new ProcessBO(idxP_l, pContextBO_p->getService(idxService_l), vRequirements_l, pmc_l));
    }
}
