#ifndef INSTANCEREADERHUMANREADABLE_HH
#define INSTANCEREADERHUMANREADABLE_HH
#include "dtoin/InstanceReaderInterface.hh"
#include <string>
#include <sstream>
using namespace std;


/**
 * Construit un Context a partir d'un fichier au format "human readable".
 * Ce format etant :
 * - destine a etre ecrit/modifie a la main
 * - pas destine a etre utilise par l'optim
 * on met l'accent sur la verification de la validite des donnees, au detriment des performances
 */
/* FIXME : Il peut etre malin de refactorer en introduisant des classes helper
 * afin que cette classe soit moins imposante...
 * ... ou pas, vu que ce n'est de toute facon pas une classe cruciale, et qu'il y a peu
 * de chances qu'on ait besoin d'y retoucher par la suite...
 */
class InstanceReaderHumanReadable : public InstanceReaderInterface {
    public:
        InstanceReaderHumanReadable();
        ~InstanceReaderHumanReadable();

        virtual ContextBO read(const string& instance_filename_p);

    protected:
        /**
         * Lit une ligne entiere du fichier, et la retourne sous forme de string
         */
        string getNextLine(istream& is_p);

        /**
         * Verifie que la ligne correspond au titre de section attendu.
         * Leve une exception si ce n'est pas le cas
         */
        void checkSectionTitle(const string& ligne_p, const string& expectedTitle_p);

        /**
         * Etant donne une ligne correspondant a un ss titre, cad de la forme
         * ==== ressource 3 / 7 ====
         * verifie que le titre (ressource), l'indice (3) et le total (7)
         * correspondent aux valeurs attendues
         * En cas d'erreur sur les donnees, une exception est levee
         */
        void checkSubTitle(const string& ligne_p, const string& subTitle_p, int idx_p, int total_p);

        /**
         * Etant donne une ligne qui correspond a une liste de valeurs, cad de la forme
         *  * mesValos : 3 4 7
         * s'assure qu'il s'agit de la liste attendu, et retourne celle-ci
         * @param ligne_p La ligne a lire
         * @param typeListe_p Le type de liste attendu. Une exception est levee si ca ne correspond pas
         */
        vector<int> readListe(const string& ligne_p, const string& typeListe_p);

        /**
         * Etant donne une ligne qui correspond a une carac, cad de la forme
         *   * myCaracs : 42
         * s'assure qu'il s'agit du bon type de carac, et retourne la valeur de celle-ci
         */
        int readCarac(const string& ligne_p, const string& typeCarac_p);

        /**
         * Etant donne une ligne correspondant a une quantite d'items, cad :
         * quantite : 3
         * parse celle-ci, et retourne cette quantite
         */
        int readQuantite(const string& ligne_p);

    private:

        void readRessources(istream& is_p, ContextBO* pContextBO_p);
        void readMachines(istream& is_p, ContextBO* pContextBO_p);
        void readServices(istream& is_p, ContextBO* pContextBO_p);
        void readProcesses(istream& is_p, ContextBO* pContextBO_p);
        void readBalanceCosts(istream& is_p, ContextBO* pContextBO_p);
        void readPoids(istream& is_p, ContextBO* pContextBO_p);

        /**
         * Etant donne une ligne qui correspond a un titre de section, cad de la forme
         * ===== my section =====
         * retourne le titre de la section
         */
        string readSectionTitle(const string& ligne_p);

        /**
         * @return TRUE si les strings a comparer sans tenir compte de la casse sont egales,
         * FALSE si elle different independamment de la casse
         */
        bool areEqualCaseInsensitive(const string& s1_p, const string& s2_p);

        /**
         * Buffer, mis ici afin de :
         * - gagner du temps en evitant de frequents new/delete
         * - pourvoir deleter dans le dtor afin de garantir 0 fuites de memoire, meme en cas de levee d'exception
         */
        char* pBuf_m;

};

#endif
