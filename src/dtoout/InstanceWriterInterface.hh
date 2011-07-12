#ifndef INSTANCEWRITERINTERFACE_HH
#define INSTANCEWRITERINTERFACE_HH
#include <string>
using namespace std;

class ContextBO;

class InstanceWriterInterface {
    public:
        virtual ~InstanceWriterInterface() = 0;
        virtual void write(ContextBO* pContextBO_p, const string& out_filename_p) = 0;
};

#endif
