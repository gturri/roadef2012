/*
 * Copyright (c) 2011 Pierre-Etienne Bougué <pe.bougue(a)gmail.com>
 * Copyright (c) 2011 Florian Colin <florian.colin28(a)gmail.com>
 * Copyright (c) 2011 Kamal Fadlaoui <kamal.fadlaoui(a)gmail.com>
 * Copyright (c) 2011 Quentin Lequy <quentin.lequy(a)gmail.com>
 * Copyright (c) 2011 Guillaume Pinot <guillaume.pinot(a)tremplin-utc.net>
 * Copyright (c) 2011 Cédric Royer <cedroyer(a)gmail.com>
 * Copyright (c) 2011 Guillaume Turri <guillaume.turri(a)gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "dtoout/SolutionDtoout.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include <limits>
using namespace std;

string SolutionDtoout::outFileName_m;
pthread_mutex_t SolutionDtoout::mutex_m = PTHREAD_MUTEX_INITIALIZER;
uint64_t SolutionDtoout::bestScoreWritten_m = numeric_limits<uint64_t>::max();
vector<int> SolutionDtoout::bestSol_m;

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

bool SolutionDtoout::writeSol(const vector<int>& vSol_p, uint64_t score_p){
    //Vu qu'on n'est pas cense passer souvent ici, on lock en global
    pthread_mutex_lock(&mutex_m);
    try {
        if (score_p >= bestScoreWritten_m) {
            pthread_mutex_unlock(&mutex_m);
            return false;
        }

        ofstream ofs_l(outFileName_m.c_str());
        if ( ! ofs_l ){
            ostringstream oss_l;
            oss_l << "Impossible d'ouvrir le flux de sortie " << outFileName_m
                << " pour y ecrire une solution" << endl;
            throw oss_l.str();
        }

        copy(vSol_p.begin(), vSol_p.end(), ostream_iterator<int>(ofs_l, " "));
        bestScoreWritten_m = score_p;
        bestSol_m = vSol_p;
    } catch (string exc) {
        pthread_mutex_unlock(&mutex_m);
        throw exc;
    } catch (std::exception exc) {
        pthread_mutex_unlock(&mutex_m);
        throw exc;
    } catch (...) {
        pthread_mutex_unlock(&mutex_m);
        throw string("Une exception a ete levee lors de l'ecriture d'une solution");
    }
    pthread_mutex_unlock(&mutex_m);
    return true;
}

uint64_t SolutionDtoout::getBestScore(){
    return bestScoreWritten_m;
}

const vector<int>& SolutionDtoout::getBestSol(){
    return bestSol_m;
}

#ifdef UTEST
void SolutionDtoout::reinit(const string& outfile_p){
    outFileName_m = outfile_p;
    pthread_mutex_unlock(&mutex_m);
    bestScoreWritten_m = numeric_limits<uint64_t>::max();
    bestSol_m.clear();
}
#endif
