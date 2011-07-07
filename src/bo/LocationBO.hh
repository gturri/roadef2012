#ifndef LOCATIONBO_HH
#define LOCATIONBO_HH
#include <tr1/unordered_set>
using namespace std::tr1;

class ServiceBO;
class MachineBO;

class LocationBO {
    public:
        LocationBO(int id_p);
        void addMachine(MachineBO* machine_p);
        int getId() const;

    private:
        int id_m;

        /**
         * Ensemble des machines de la Location
         */
        unordered_set<MachineBO*> machines_m;
};

#endif
