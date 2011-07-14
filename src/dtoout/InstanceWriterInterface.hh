#ifndef INSTANCEWRITERINTERFACE_HH
#define INSTANCEWRITERINTERFACE_HH
#include <string>
using namespace std;

class ContextBO;

class InstanceWriterInterface {
    public:
        virtual ~InstanceWriterInterface() = 0;

        /**
         * Ecrit dans un fichier
         */
        void write(ContextBO* pContextBO_p, const string& out_filename_p);

        /**
         * Ecrit sur un flux de sortie
         */
        void write(ContextBO* pContextBO_p, ostream& os_p);

        /**
         * Ecrit sur une string
         * Wrapper de writeOnString afin d'eviter une forme de shadowing
         */
        string write(ContextBO* pContextBO_p);

    protected:
        virtual string writeOnString(ContextBO* pContextBO_p) = 0;
};

#endif
