#ifndef SOLUTIONDTOIN_HH
#define SOLUTIONDTOIN_HH
#include <iostream>
using namespace std;

class ContextBO;

/**
 * Classe en charge de la lecture du fichier de solution initial
 */
class SolutionDtoin {
    public:
        void read(istream& is_p, ContextBO* pContextBO_p);
};

#endif
