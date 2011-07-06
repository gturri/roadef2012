#ifndef PROCESSBO_HH
#define PROCESSBO_HH
#include <tr1/unordered_map>
using namespace std::tr1;

class MachineBO;
class RessourceBO;
class ServiceBO;

class ProcessBO {
    private:
        int id_m;
        ServiceBO* service_m;
        unordered_map<Ressource*, int> requirement_m;
        Machine* machineInit_m;
        int pmc_m;
};


#endif
