#ifndef SOLUTIONDTOOUT_HH
#define SOLUTIONDTOOUT_HH
#include <fstream>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdint.h>
using namespace std;

class ContextBO;
class ContextALG;

/**
 * Classe en charge de l'ecriture de la meilleure solution
 *
 * Cette classe assure aussi la gestion de la memorisation du meilleur score/solution
 * Ces donnees sont initialisees sur la solution initiale. L'initialisation est assuree par le main
 */
class SolutionDtoout {
    public: /**
         * Permet de setter le nom du fichier sur lequel ecrire
         */
        static void setOutFileName(const string& outFileName_p);

        /**
         * Ecrit la solution initiale sur le fichier specifie
         * (Cette methode n'utilise pas le fichier par defaut, celui-ci etant "reserve" a la meilleure solution de l'optim)
         */
        static void writeSolInit(ContextBO* pContextBO_p, const string& outFileName_p);

        /**
         * Ecrit la solution, si elle bat la meilleure connue jusque la
         * @param vSol_p La solution a ecrire
         * @param score_p Le score de la solution (aucune verification n'est faite !)
         * @return TRUE si la solution a ete ecrite
         */
        static bool writeSol(const vector<int>& vSol_p, uint64_t score_p);

        static uint64_t getBestScore();

        /**
         * Retourne la meilleure solution trouvee jusque la (de score #getBestScore())
         * Si aucune ecriture n'a eu lieu, retoune un vecteur vide (et le best score est "infini")
         * Le main est cense assurer cette premiere ecriture, sur la sol init, donc
         * les classes appellantes ne devraient pas se soucier de ce point
         */
        static const vector<int>& getBestSol();

    private:
        /**
         * Fichier sur lequel la solution doit etre ecrite
         */
        static string outFileName_m;

        /**
         * Score de la meilleure solution ecrite
         */
        static uint64_t bestScoreWritten_m;

        static vector<int> bestSol_m;

        /**
         * Mutex utilise pour garantir qu'on ecrira pas deux solution en meme temps
         * 
         * Nb : cas un peu plus sioux que juste l'ecriture simultanee dans le fichier (que l'on gere aussi) :
         * - le meilleur score est 1000
         * - un thread t1 veut ecrire une solution a 800, passe le check du score et est mis en pause
         * - un thread t2 veut ecrire une solution a 900, passe le check du score est en mis en pause
         *  - t1 s'ecrit
         *  - t2 s'ecrit et fait perdre la solution a 900
         *  C'est pour eviter ca qu'il faut maintenant passer le score a #writeSol
         */
        static pthread_mutex_t mutex_m;
};

#endif
