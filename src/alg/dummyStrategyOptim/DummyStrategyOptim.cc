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

#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Checker.hh"
#include "tools/Log.hh"
#include <algorithm>
#include <cassert>
using namespace std;

ContextALG DummyStrategyOptim::run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p, const variables_map& opt_p){
    vector<int> sol_l = contextAlg_p.getCurrentSol();

    /* "ContextAlg, cette solution est peut etre mieux que ce que tu connais, 
     * mais peut etre pas. Verifie le, et met toi a jour si c'est le cas"
     */
    if ( contextAlg_p.checkCompletAndMajBestSol(sol_l, true) ){
        LOG(USELESS) << "La solution initialement sur le contextALG envoie du pate !" << endl;
    }

    /* J'echange les machines des deux premiers processes, et rebelote
     */
    if ( sol_l.size() > 1 ){
        swap(sol_l[0], sol_l[1]);
        if ( contextAlg_p.checkCompletAndMajBestSol(sol_l, true) ){
            LOG(USELESS) << "C'etait une bonne idee d'echanger les machines des 2 premiers process" << endl;
        }
    }

    /* Je met arbitraitement le 1er process sur la 1ere machine.
     * Je teste ce que ca donne sans deleguer ces operations au contextAlg.
     */
    sol_l[0] = 0;
    Checker checker_l(&contextAlg_p);
    int scoreAvant_l = checker_l.computeScore();
    if ( checker_l.isValid() ){
        Checker checker2_l(contextAlg_p.getContextBO(), sol_l);
        int scoreApres_l = checker2_l.computeScore();
        if ( scoreApres_l > scoreAvant_l ){
            bool bestSolMaj_l = SolutionDtoout::writeSol(sol_l, scoreApres_l);

            /* Ici, on a verifie qu'on a une meilleure sol que ce qu'on avait avant.
             * On est donc sur que le contextALG a fait sa maj
             */
            assert(bestSolMaj_l);

            LOG(USELESS) << "La sol avec le process 0 sur la machine 0 monte le score de " << scoreAvant_l << " a " << scoreApres_l << endl;
        } else {
            LOG(USELESS) << "La sol avec le process 0 sur la machine 0 diminue le score de " << scoreAvant_l << " a " << scoreApres_l << endl;
        }
    } else {
        LOG(USELESS) << "En mettant le process 0 sur la machine 0, on a une sol non reglementaire" << endl;
    }

    /* On souhaite que la prochaine strategie (s'il y en a une) considere comme solution courante la derniere qu'on a considere
     * (cette strategie pourra, si elle le desire, ignorer cette solution initial qu'on lui fourni)
     */

    contextAlg_p.setCurrentSol(sol_l);
    return contextAlg_p;
}
