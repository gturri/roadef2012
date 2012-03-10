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

#include "MonteCarloSimulationALG.hh"
#include "SolutionALG.hh"
#include "tools/Log.hh"

#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;

boost::mt19937 MonteCarloSimulationALG::gen_m;

int MonteCarloSimulationALG::roll_die(int maxRange_p) 
{
    boost::uniform_int<> dist(0, std::max(0,maxRange_p-1));
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen_m, dist);
    return die();
}


MonteCarloSimulationALG::MonteCarloSimulationALG()    
{
}

MonteCarloSimulationALG::~MonteCarloSimulationALG()
{
}

void MonteCarloSimulationALG::run(SolutionALG * pSolution_p)
{
    // remplir la solution actuellement vide
    // -> passer le contexte aussi?
    // -> donner une solution sans affectation?
    
    bool foundSomethingToAssign_l = true;
    while (foundSomethingToAssign_l)
    {
        typedef vector<SolutionALG::ProcessId> ProcessPool;
        ProcessPool processes_l = pSolution_p->getAvaiableProcesses();
        int nbAvaiableProcesses_l = processes_l.size();
        if(nbAvaiableProcesses_l)
        {
            SolutionALG::ProcessId process_l = processes_l[roll_die(nbAvaiableProcesses_l)];
            typedef vector<SolutionALG::MachineId> MachinePool;
            MachinePool machines_l = pSolution_p->getAvaiableMachines(process_l);
            int nbAvaiableMachines_l = machines_l.size();
            if( nbAvaiableMachines_l )
            {
                SolutionALG::MachineId machine_l = machines_l[roll_die(nbAvaiableMachines_l)];
                pSolution_p->assign(process_l,machine_l);
            }
            else
            {
                pSolution_p->assign(process_l,SolutionALG::failToAssign);
            }
        }
        else
        {
           foundSomethingToAssign_l = false; 
        }
    }
}
