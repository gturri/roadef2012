#ifndef RANDOMGENERATEUR_HH
#define RANDOMGENERATEUR_HH
#include <vector>
using namespace std;


class RandomCore;

/**
 * Classe en charge des tirages aleatoires.
 *
 * Interets :
 * - Centralisation de la logique stochastique de l'application (et donc evite de la duplication de code, simplifie la maintenance, ...)
 * - Centralise la gestion de la graine (evite que plusieurs classes fassent chacune leur srand)
 * - Permet de decoupler la logique de simulation de lois exotiques, et la problematique de la qualite du "randomCore"
 *
 * Concept :
 * Cette classe se base sur un #RandomCore, charge de simuler une loi aleatoire uniforme sur [0, 1[,
 * afin de decoupler cette implantation, et la generation de tirages plus elabores a partir de celle-ci
 *
 * Notes en vrac :
 * - Si aucun appel a #setRandomCore n'est effectue, un core par defaut est utilise
 */
class RandomGenerateur {
  public:
    ~RandomGenerateur();

    static RandomGenerateur* getInstance();

    /**
     * Supprime l'unique instance du singleton.
     * L'un des seuls interets de cette methode est de permettre d'eviter d'avoir des fuites "fictives" sur valgrind, et donc, d'avoir des donnees plus facile a interpreter
     * Attention : apres cet appel, tous les pointeurs sur un (le) RandomGenerateur ne seront plus valides
     */
    static void cleanSingleton();

    /**
     * Initialise (ou maj) la graine du #RandomCore utilise
     */
    void setSeed(long seed_p);


    /**
     * Le RandomGenerateur se charge de la destruction de cet objet
     * @param core_p L'implantation de RandomCore a utiliser
     * @param reinitSeed_p true s'il faut initialiser la graine de cet objet (l'argument utilise est celui-ci fourni lors du dernier appel a #setSeed)
     */
    void setRandomCore(RandomCore* core_p, bool reinitSeed_p = true);

    /**
     * Genere une realisation d'une loi uniforme sur [min_p, max_p[
     * @param min_p Borne min
     * @param max_p Borne sup (cette valeur n'est pas generable)
     * @pre min_p < max_p
     */
    double generateUniformeDouble(double min_p, double max_p);

    /**
     * Genere une realisation d'une loi uniforme sur [min_p, max_p[
     * @param min_p Borne min
     * @param max_p Borne sup (cette valeur n'est pas generable)
     * @pre min_p < max_p
     */
    int generateUniformeInt(int min_p, int max_p);

    /**
     * Genere un vecteur de k entiers aleatoires distincts dans [0, n[, suivant une loi uniforme
     * @param k_p le nombre d'elements a piocher
     * @param n_p la taille de l'intervalle
     * @pre k <= n
     */
    vector<int> tirageAleatoireSansRemise(int k_p, int n_p);

    /**
     * Genere une realisation d'une loi normale de moyenne mu_p et de variance sigma_p*sigma_p
     */
    double generateNormale(double mu_p, double sigma_p);

    /**
     * Approximation de l'inverse de la fonction de repartition de la loi normale
     */
    double inverseProbNorm(double& x) const;



  private:
    RandomGenerateur();

    /**
     * Unique instance permettant de gerer le singleton
     */
    static RandomGenerateur* mySingleton_m;
    
    /**
     * Implantation du generateur utilise pour generer des nombres aleatoires uniformes sur [0, 1[
     */
    RandomCore* core_m;


    /**
     * Conserver ce parametre permet de le re-setter lors du futurs appels a setRandomCore
     */
    long seed_m;

};

#endif
