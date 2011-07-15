#ifndef RESSOURCEBO_HH
#define RESSOURCEBO_HH

class RessourceBO {
    public:
        RessourceBO(int id_p, bool isTransient_p, int loadCost_p);
        int getId() const;
        bool isTransient() const;
        int getWeightLoadCost() const;

        bool operator==(const RessourceBO& ress_l) const;
        bool operator!=(const RessourceBO& ress_l) const;

    private:
        /**
         *id 0-based qui correspond a l'ordre dans lequel la ressource est lue
         */
        int id_m;

        /**
         * Si TRUE, alors cette ressource n'est pas liberee d'une machine lorsqu'on en enleve un process (cf sujet)
         */
        bool isTransient_m;

        /**
         * Poids dans la fonction objectif.
         * Coef multiplicatif a appliquer a la somme des depassement des safety capacity
         */
        int weightLoadCost_m;
};

#endif
