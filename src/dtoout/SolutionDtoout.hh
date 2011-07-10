#ifndef SOLUTIONDTOOUT_HH
#define SOLUTIONDTOOUT_HH
#include <fstream>
#include <string>
using namespace std;

/**
 * Classe en charge de l'ecriture de la meilleure solution
 */
class SolutionDtoout {
    public:
        /**
         * Permet de setter le nom du fichier sur lequel ecrire
         */
        static void setOutFileName(const string& outFileName_p);

        //TODO : ajouter les methodes d'ecriture, une fois que des formats de solution seront determines


    private:
        /**
         * Fichier sur lequel la solution doit etre ecrite
         */
        static string outFileName_m;
};

#endif
