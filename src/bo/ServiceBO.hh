#ifndef SERVICEBO_HH
#define SERVICEBO_HH
#include <tr1/unordered_set>
#include <tr1/unordered_map>
using namespace std::tr1;

class ProcessBO;
class NeighborhoodBO;

class ServiceBO {
    public:
        ServiceBO(int id_p, int spreadMin_p, const unordered_set<int>& dependances_p);

        int getId() const;
        int getSpreadMin() const;

        /**
         * Retourne le nombre de services dont "this" depend
         */
        int getNbServicesIDependOn() const;

        /**
         * Indique si "this" depend du service d'indice donne
         */
        bool iDependOn(int idxService_p) const;

        void addProcess(ProcessBO* pProcess_p);
        int getNbProcesses() const;
        bool containsProcess(int idxProcess_p) const;

    private:
        const int id_m;

        /**
         * Liste des indices de processes appartenant au service
         */
        unordered_set<int> sProcess_m;

        /**
         * Nombre minimum de locations sur lesquels les processes du services
         * doivent etre deployes
         */
        const int spreadMin_m;

        /**
         * Contient les indices des services dont "this" depend
         */
        const unordered_set<int> iDependOnThem_m;
};


#endif
