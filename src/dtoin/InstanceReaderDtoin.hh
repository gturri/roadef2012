#ifndef INSTANCEREADERDTOIN_HH
#define INSTANCEREADERDTOIN_HH
#include <string>
using namespace std;
#include "bo/ContextBO.hh"


class InstanceReaderDtoin {
    public:
        static ContextBO read(const string& instance_filename_p);

};

#endif
