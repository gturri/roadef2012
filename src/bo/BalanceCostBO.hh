#ifndef BALANCECOSTBO_HH
#define BALANCECOSTBO_HH

class RessourceBO;

/**
 * Les balance costs interviennent dans la fonction objectif.
 * Un balance cost donne ajoute un cout egal a :
 *
 * poids_m * (somme sur les machine de : [ max(0, target_m*A(m, pRess1_m), - 1(m, pRess2_m) ] )
 *
 * ou A(m, pRess_m) = C(m, pRess_m) - U(m, pRess_m), cad la quantite de pRess_m encore dispo
 */
class BalanceCostBO{
    public:
        BalanceCostBO(RessourceBO* pRess1_p, RessourceBO* pRess2_p, int target_p, int poids_p);

        RessourceBO* getRessource1() const;
        RessourceBO* getRessource2() const;
        int getTarget() const;
        int getPoids() const;


    private:
        RessourceBO* const pRess1_m;
        RessourceBO* const pRess2_m;
        const int target_m;
        const int poids_m;
};

#endif
