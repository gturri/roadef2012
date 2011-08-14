#include "dtoout/SolutionDtoout.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
using namespace std;

string SolutionDtoout::outFileName_m;

void SolutionDtoout::setOutFileName(const string& outFileName_p){
    outFileName_m = outFileName_p;
}

void SolutionDtoout::writeSolInit(ContextBO* pContextBO_p, const string& outFileName_p){
    ofstream ofs_l(outFileName_p.c_str());
    if ( ! ofs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le flux de sortie " << outFileName_m
            << " pour y ecrire une solution initiale" << endl;
        throw oss_l.str();
    }

    int nbProcess_l = pContextBO_p->getNbProcesses();
    for ( int idxP_l=0 ; idxP_l < nbProcess_l ; idxP_l++ ){
        ofs_l << pContextBO_p->getProcess(idxP_l)->getMachineInit()->getId();
        if ( idxP_l != nbProcess_l ){
            ofs_l << " ";
        }
    }
}

void SolutionDtoout::writeSol(const vector<int>& vSol_p){
    ofstream ofs_l(outFileName_m.c_str());
    if ( ! ofs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le flux de sortie " << outFileName_m
            << " pour y ecrire une solution" << endl;
        throw oss_l.str();
    }

    copy(vSol_p.begin(), vSol_p.end(), ostream_iterator<int>(ofs_l, " "));
}
