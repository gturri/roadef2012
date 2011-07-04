#ifndef RANDOMCORE_HH
#define RANDOMCORE_HH

/**
 * Interface decrivant un generateur de nombres aleatoires uniformes sur [0, 1[ uniquement.
 * Cette classe est destine a n'etre utilisee qu'a travers #RandomGenerateur (qui rajoute une surcouche permettant de generer davantage de lois a partir de celle-ci)
 */
class RandomCore {
  public:
    virtual ~RandomCore(){}

    virtual void setSeed(long seed_p) = 0;

    /**
     * Genere un nombre suivant une loi uniforme sur [0, 1[
     */
    virtual double generate() = 0;

};

#endif
