#ifndef MACHINEBO_HH
#define MACHINEBO_HH
#include <vector>
using namespace std;

class LocationBO;
class NeighborhoodBO;
class RessourceBO;

class MachineBO {
    public:
        MachineBO(int id_p, LocationBO* location_p, NeighborhoodBO* neighborhood_p, const vector<int>& capa_p, const vector<int> safetyCapa_p);
        bool operator==(MachineBO& machine_p) const;
        bool operator!=(MachineBO& machine_p) const;

        int getId() const;
        LocationBO* getLocation() const;
        NeighborhoodBO* getNeighborhood() const;
        int getCapa(int idxRess_p) const;
        int getCapa(RessourceBO const * pRess_p) const;
        vector<int> getCapas() const;
        int getSafetyCapa(int idxRess_p) const;
        vector<int> getSafetyCapas() const;

    private:
        int id_m;
        LocationBO* const location_m;
        NeighborhoodBO* const neighborhood_m;

        /**
         * capa_m[idxRess] = capacite de la machine par rapport a cette ressource
         */
        const vector<int> capa_m;

        /**
         * safetyCapa_m[idxRess] = capacite de securite de la machine par rapport a cette ressource
         */
        const vector<int> safetyCapa_m;
};

#endif
