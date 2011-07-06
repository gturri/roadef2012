#ifndef MACHINEBO_HH
#define MACHINEBO_HH
#include <tr1/unordered_map>
using namespace std::tr1;

class LocationBO;
class NeighborhoodBO;
class RessourceBO;

class MachineBO {
    public:
        Machine(int id_l, LocationBO* location_l, NeighborhoodBO* neighborhood_l, const unordered_map<RessourceBO*, int>& capa_m, const unordered_map<RessourceBO*, int> safetyCapa_m);

    private:
        int id_m;
        LocationBO* location_m;
        NeighborhoodBO* neighborhood_m;
        unordered_map<RessourceBO*, int> capa_m;
        unordered_map<RessourceBO*, int> safetyCapa_m;
        unordered_map<RessourceBO*, int> capaLeft_m;
};

#endif
