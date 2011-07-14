#ifndef INSTANCEREADERINTERFACE_HH
#define INSTANCEREADERINTERFACE_HH
#include <string>
using namespace std;

#include "bo/ContextBO.hh"

/**
 * Classe en charge de la lecture du fichier d'instance.
 * On lui file un nom de fichier, et il construit tous les objets bo qui en decoulent,
 * les stocke dans un ContextBO, et retourne ce dernier.
 */
class InstanceReaderInterface {
    public:
        virtual ~InstanceReaderInterface();
        virtual ContextBO read(const string& instance_filename_p) = 0;
};

#endif
