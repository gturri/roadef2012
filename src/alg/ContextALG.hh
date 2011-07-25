#ifndef CONTEXTALG_HH
#define CONTEXTALG_HH

#include <vector>
using namespace std;

class ContextBO;

class ContextALG {
    public:
        ContextALG(ContextBO const * pContextBO_p);
        ContextBO const * getContextBO() const;

        vector<int> getCurrentSol() const;

    private:
        /**
         * Represente l'instance en cours.
         * Plusieurs ContextALG peuvent partager le meme ContextBO,
         * donc il va appartenir aux classes clients de gerer le delete du ContextBO
         * De meme, cet attribut ne justifie ni un operator= ni un cpy ctr customise
         */
        ContextBO const * pContextBO_m;

        /**
         * vecteur de taille nbProcesses representant la solution actuelle
         * currentSol_m[idxProcess] = idxMachine sur laquelle il est affecte
         */
        vector<int> currentSol_m;
};

#endif
