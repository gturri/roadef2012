#include "dtoin/ServiceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ServiceBO.hh"
#include <tr1/unordered_set>
using namespace std;

void ServiceDtoin::read(istream& ifs_p, ContextBO* pContextBO_p){
    int nbServices_l;
    ifs_p >> nbServices_l;

    for ( int idxService_l=0 ; idxService_l < nbServices_l ; idxService_l++ ){
        int spreadMin_l, nbDependances_l;
        ifs_p >> spreadMin_l >> nbDependances_l;
        unordered_set<int> dependances_l;

        for ( int idxDep_l=0 ; idxDep_l < nbDependances_l ; idxDep_l++ ){
            int idxServiceDep_l;
            ifs_p >> idxServiceDep_l;
            dependances_l.insert(idxServiceDep_l);
        }

        pContextBO_p->addService(new ServiceBO(idxService_l, spreadMin_l, dependances_l));
    }
}
