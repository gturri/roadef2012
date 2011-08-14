#ifndef SOLUTIONDTOOUT_HH
#define SOLUTIONDTOOUT_HH
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class ContextBO;
class ContextALG;

/**
 * Classe en charge de l'ecriture de la meilleure solution
 */
class SolutionDtoout {
    public:
        /**
         * Permet de setter le nom du fichier sur lequel ecrire
         */
        static void setOutFileName(const string& outFileName_p);

        /**
         * Ecrit la solution initiale sur le fichier specifie
         * (Cette methode n'utilise pas le fichier par defaut, celui-ci etant "reserve" a la meilleure solution de l'optim)
         */
        static void writeSolInit(ContextBO* pContextBO_p, const string& outFileName_p);

        static void writeSol(const vector<int>& vSol_p);
    private:
        /**
         * Fichier sur lequel la solution doit etre ecrite
         */
        static string outFileName_m;
};

#endif
