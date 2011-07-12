#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterDtoout.hh"

shared_ptr<InstanceWriterInterface> WriterSelecter::getWriter(const string& writer_p){
    shared_ptr<InstanceWriterInterface> result_l(new InstanceWriterDtoout);
    return result_l;
}
