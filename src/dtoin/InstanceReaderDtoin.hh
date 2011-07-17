#ifndef INSTANCEREADERDTOIN_HH
#define INSTANCEREADERDTOIN_HH
#include <string>
using namespace std;

#include "dtoin/InstanceReaderInterface.hh"
#include "bo/ContextBO.hh"

class InstanceReaderDtoin : public InstanceReaderInterface {
    public:
        virtual ContextBO read(const string& instance_filename_p);

};

#endif
