#ifndef SERVICEBO_HH
#define SERVICEBO_HH
#include <tr1/unordered_set>
#include <tr1/unordered_map>
using namespace std::tr1;

class ProcessBO;
class LocationBO;
class NeighborhoodBO;

class ServiceBO {
    private:
        int id_m;
        unordered_map<LocationBO*, int> nbProcessPerLocation_m;
        unordered_set<ProcessBO*> process_m;
        int spreadMin;
        unordered_set<NeighborhoodBO*> neighborhood_m;
        unordered_set<Service*> IDependOnThem_m;
        unordered_set<Service*> theyDependsMe_m;
        int serviceMoveCost_m;
};


#endif
