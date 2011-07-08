#ifndef SERVICEBO_HH
#define SERVICEBO_HH
#include <tr1/unordered_set>
#include <tr1/unordered_map>
using namespace std::tr1;

class ProcessBO;
class LocationBO;
class NeighborhoodBO;

class ServiceBO {
    public:
        ServiceBO(int id_p);

        int getId() const;
        int getSpreadMin() const;

        /**
         * Retourne le nombre de services dont "this" depend
         */
        int getNbServicesIDependOn() const;

        /**
         * Indique si "this" depend du service d'indice donne
         */
        bool iDependOn(int idx_p) const;

    private:
        int id_m;
        unordered_map<LocationBO*, int> nbProcessPerLocation_m;
        unordered_set<ProcessBO*> process_m;
        int spreadMin;
        unordered_set<NeighborhoodBO*> neighborhood_m;

        /**
         * Contient les indices des services dont "this" depend
         */
        unordered_set<int> iDependOnThem_m;

        int serviceMoveCost_m;
};


#endif
