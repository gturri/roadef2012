#ifndef MONTECARLOTREESEARCHALG_HH
#define MONTECARLOTREESEARCHALG_HH

/** Classe qui effectue la recherche. A partir de l'arbre de decision, elle
    effectue une descente suivant la formule magique en replissant au fur et
    a mesure la classe SpaceALG courante. Par le biais de cette derniere, elle
    va ensuite generer les fils de la feuille courante puis lancer sur ceux-ci
    des simulations et des recherches locales a partir de l'espace courant.
    L'information est finalement remonter pour effectuer la prochaine descente.
 */

class SolutionALG;
class SpaceALG;
class TreeALG;

class MonteCarloTreeSearchALG
{
    public:
    	MonteCarloTreeSearchALG();
    	~MonteCarloTreeSearchALG();

    	SolutionALG * search();

    	void setpTree(TreeALG *);
    	TreeALG * getpTree() const;

    private:
    	SpaceALG * initNewSpace();
    	SpaceALG * performDescent();
    	
    	
    	TreeALG * pTree_m;
};

#endif
