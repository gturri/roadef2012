#ifndef MACHINEDTOIN_HH
#define MACHINEDTOIN_HH
#include <fstream>
#include <vector>
using namespace std;

class ContextBO;
class LocationBO;
class NeighborhoodBO;
class RessourceBO;

/**
 * Classe jetable : on l'instancie, on appelle read une fois, et puis c'est tout.
 * Une instance n'est pas faite pour etre utilisable deux fois (parce que semantiquement ca n'a pas de sens, et parce que c'est plus simple de l'implanter ainsi)
 */
class MachineDtoin{
    public:
        MachineDtoin();

        /**
         * @param ifs_p Le flux a lire
         * @param pContextBO_p Le context a peupler
         */
        void read(ifstream& ifs_p, ContextBO* pContextBO_p);

    private:
        vector<int> readQteRess(ifstream& ifs_p);
        void readMMCForOneMachine(ifstream& ifs_p, int idxCurMachine_p);

        void sendMMC() const;
        void sendLocations() const;
        void sendNeighborhoods() const;

        /**
         * Si la location demandee n'existe pas, elle est creee a la volee
         */
        LocationBO* getLocation(int idx_p);

        /**
         * Si le neighborhood n'existe pas, il est cree a la volee
         */
        NeighborhoodBO* getNeighborhood(int idx_p);

        vector<LocationBO*> pLoc_m;
        vector<NeighborhoodBO*> pNeigh_m;
        ContextBO* pContext_m;
        
        vector<vector<int> > mmcCosts_m;


        bool alreadyUsed_m;
};

#endif
