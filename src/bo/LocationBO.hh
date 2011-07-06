#ifndef LOCATIONBO_HH
#define LOCATIONBO_HH
#include <tr1/unordered_set>
using namespace std::tr1;

class ServiceBO;

class LocationBO {
    private:
        int id_m;
        unordered_set<MachineBO*> machines_m;
        unordered_set<ServiceBO*> services_m;
};

#endif
