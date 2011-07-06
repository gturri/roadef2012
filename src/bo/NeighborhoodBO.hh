#ifndef NEIGHBORHOODBO_HH
#define NEIGHBORHOODBO_HH
#include <tr1/unordred_set>
using namespace st::tr1;

class MachineBO;
class ServiceBO;

class NeighborhoodBO {
    private:
        int id;
        unordred_set<MachineBO*> machines_m;
        unordred_set<Service*> services_m;
};

#endif;
