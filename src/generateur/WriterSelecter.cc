#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/InstanceWriterHumanReadable.hh"
#include "tools/Log.hh"

shared_ptr<InstanceWriterInterface> WriterSelecter::getWriter(const string& writer_p){
    shared_ptr<InstanceWriterInterface> result_l(new InstanceWriterDtoout);

    if ( writer_p == "human" ){
        LOG(DEBUG) << "Ecriture de l'instance via un 'human readable writer'" << endl;
        result_l = shared_ptr<InstanceWriterInterface>(new InstanceWriterHumanReadable);
    } else {
        LOG(DEBUG) << "Ecriture de l'instance via le writer officiel (choix par defaut)" << endl;
    }

    return result_l;
}
