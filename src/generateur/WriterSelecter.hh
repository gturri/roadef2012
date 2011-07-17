#ifndef WRITERSELECTER_HH
#define WRITERSELECTER_HH
#include "dtoout/InstanceWriterInterface.hh"
#include <memory>
using namespace std;


class WriterSelecter {
    public:
        static shared_ptr<InstanceWriterInterface> getWriter(const string& writer_p);
};

#endif
