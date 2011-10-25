#ifndef MONTECARLOTREESEARCHALG_HH
#define MONTECARLOTREESEARCHALG_HH

/** Classe qui effectue la recherche. A partir de l'arbre de decision, elle
    effectue une descente suivant la formule magique en replissant au fur et
    a mesure la classe SpaceALG courante. Par le biais de cette derniere, elle
    va ensuite generer les fils de la feuille courante puis lancer sur ceux-ci
    des simulations et des recherches locales a partir de l'espace courant.
    L'information est finalement remonter pour effectuer la prochaine descente.
 */

#include "TreeALG.hh"
#include "TreeSimpleImplALG.hh"

class SolutionALG;
class SpaceALG;

class MonteCarloTreeSearchALG
{
    public:
        typedef TreeALG< TreeSimpleImplALG<NodeContentALG> > Tree;
        
        MonteCarloTreeSearchALG();
        ~MonteCarloTreeSearchALG();
        
        void search();
        
        void setpTree(Tree *);
        Tree * getpTree() const;

        void setpInitialSpace(SpaceALG *); 
        
    private:
        SpaceALG * initNewSpace();
        int performDescent();
        
        Tree * pTree_m;
        SpaceALG * pInitialSpace_m;
};

#endif
