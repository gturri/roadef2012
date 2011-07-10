#ifndef SOLUTIONDTOIN_HH
#define SOLUTIONDTOIN_HH
#include <iostream>
#include <string>
using namespace std;

class ContextBO;

/**
 * Classe en charge de la lecture du fichier de solution initial
 */
class SolutionDtoin {
    public:
        /**
         * Lit le fichier de solution (designe par son nom)
         */
        static void read(const string& solFileName_p, ContextBO* pContextBO_p);

        /**
         * Lit le flux representant le fichier de solution
         */
        static void read(istream& is_p, ContextBO* pContextBO_p);
};

#endif
