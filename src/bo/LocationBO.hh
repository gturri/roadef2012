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
        void addMachine(int idxMachine_p);
        int getId() const;

        bool operator==(const LocationBO& loc_p) const;
        bool operator!=(const LocationBO& loc_p) const;

    private:
        int id_m;

        /**
         * Ensemble des id des machines de la Location
         */
        unordered_set<int> machines_m;
};

#endif
