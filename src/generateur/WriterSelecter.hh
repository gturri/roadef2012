#ifndef WRITERSELECTER_HH
#define WRITERSELECTER_HH
#include "dtoout/InstanceWriterInterface.hh"
#include <boost/shared_ptr.hpp>
using namespace boost;
using namespace std;


class WriterSelecter {
    public:
        static shared_ptr<InstanceWriterInterface> getWriter(const string& writer_p);
};

#endif
