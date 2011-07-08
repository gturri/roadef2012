#ifndef CONTEXTBO_HH
#define CONTEXTBO_HH
#include <vector>
using namespace std;

class RessourceBO;
class MachineBO;
class LocationBO;
class NeighborhoodBO;
class MMCBO;
class ServiceBO;

//FIXME : Si cette classe grossie trop, ajouter des managerBO pour chaque type d'objet gere actuellement par le ContextBO
class ContextBO {
    public:
        ContextBO();
        ~ContextBO();

        void setMMCBO(MMCBO* pMMC_p);
        MMCBO* getMMCBO() const;

        void addRessource(RessourceBO* pRess_p);
        int getNbRessources() const;
        RessourceBO* getRessource(int id_p) const;

        void addLocation(LocationBO* pLoc_p);
        int getNbLocations() const;
        LocationBO* getLocation(int idx_p) const;

        void addNeighborhood(NeighborhoodBO* pNeigh_p);
        int getNbNeighborhoods() const;
        NeighborhoodBO* getNeihborhood(int idx_p) const;

        void addMachine(MachineBO* pMachine_p);
        int getNbMachines() const;
        MachineBO* getMachine(int idx_p) const;

        int getNbServices() const;
        ServiceBO* getService(int idx_p) const;

    private:
        vector<RessourceBO*> ressources_m;
        vector<MachineBO*> machines_m;
        vector<LocationBO*> locations_m;
        vector<NeighborhoodBO*> neighborhoods_m;
        MMCBO* pMMCBO_m;
};

#endif
