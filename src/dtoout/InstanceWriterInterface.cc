#include "dtoout/InstanceWriterInterface.hh"
#include <fstream>
#include <sstream>

InstanceWriterInterface::~InstanceWriterInterface(){}

void InstanceWriterInterface::write(ContextBO* pContextBO_p, const string& out_filename_p){
    ofstream ofs_p(out_filename_p.c_str());
    if ( ! ofs_p ){
        ostringstream oss_l;
        oss_l << "Impossible de dumper l'instance dans le fichier " << out_filename_p << endl;
        throw oss_l.str();
    }

    write(pContextBO_p, ofs_p);
}

void InstanceWriterInterface::write(ContextBO* pContextBO_p, ostream& os_p){
    os_p << write(pContextBO_p);
}

string InstanceWriterInterface::write(ContextBO* pContextBO_p){
    return writeOnString(pContextBO_p);
}
