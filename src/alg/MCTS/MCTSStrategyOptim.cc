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

#include "MCTSStrategyOptim.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Checker.hh"
#include "tools/Log.hh"

#include "ConstraintSystemALG.hh"
#include "EvaluationSystemALG.hh"
#include "oneprocessdecisions/OPPMSpaceALG.hh"
#include "MonteCarloTreeSearchALG.hh"
#include "TreeSimpleImplALGDefs.hh"
#include "TreeALGDefs.hh"

#ifdef USE_GECODE
#include "cpdecisions/CPSpaceALG.hh"
#endif

using namespace std;

ContextALG MCTSStrategyOptim::run( ContextALG contextAlg_p,
                                   time_t heureFinMaxPreconisee_p,
                                   boost::program_options::variables_map const & argv_p) {
    const vector<int>& sol_l = contextAlg_p.getCurrentSol();

    /* "ContextAlg, cette solution est peut etre mieux que ce que tu connais, 
     * mais peut etre pas. Verifie le, et met toi a jour si c'est le cas"
     */
    if ( contextAlg_p.checkCompletAndMajBestSol(sol_l, true) ){
        LOG(USELESS) << "La solution initialement sur le contextALG envoie du pate !" << endl;
    }

    LOG(USELESS) << "initialisation des objets" << endl;
    Checker checker_l(&contextAlg_p);
    EvaluationSystemALG evaluation_l;
    evaluation_l.setpContext(&contextAlg_p);
    ConstraintSystemALG constraints_l;
    constraints_l.setpContext(&contextAlg_p);
#ifdef USE_GECODE
    CPSpaceALG * pInitialSpace_l = new CPSpaceALG;
#else
    OPPMSpaceALG * pInitialSpace_l = new OPPMSpaceALG;
#endif
    pInitialSpace_l->setpConstraintSystem(&constraints_l);
    pInitialSpace_l->setpEvaluationSystem(&evaluation_l);
    pInitialSpace_l->setpContext(&contextAlg_p);
    
    LOG(USELESS) << "construction de l'arbre" << endl;
    MonteCarloTreeSearchALG mcts_l;
    TreeALG< TreeSimpleImplALG<NodeContentALG> > tree_l;
    mcts_l.setpTree(&tree_l);
    mcts_l.setpInitialSpace(pInitialSpace_l);
    
    LOG(INFO) << "Lauching MCTS" << endl;
    mcts_l.search();

    /* On souhaite que la prochaine strategie (s'il y en a une) considere comme
     * solution courante la derniere qu'on a considere (cette strategie pourra,
     * si elle le desire, ignorer cette solution initial qu'on lui fourni)
     */

    contextAlg_p.setCurrentSol(SolutionDtoout::getBestSol());
    return contextAlg_p;
}
