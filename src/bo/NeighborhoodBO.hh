#ifndef NEIGHBORHOODBO_HH
#define NEIGHBORHOODBO_HH
#include <tr1/unordered_set>
using namespace std::tr1;

class MachineBO;
class ServiceBO;

class NeighborhoodBO {
    public:
        NeighborhoodBO(int id_p);
        void addMachine(MachineBO* machine_p);
        int getId() const;

    private:
        int id_m;

        /**
         * Ensemble des id des machines du neighborhood
         */
        unordered_set<int> machines_m;
};

#endif
