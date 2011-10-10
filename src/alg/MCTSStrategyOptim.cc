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

using namespace std;

ContextALG MCTSStrategyOptim::run( ContextALG contextAlg_p,
                                   time_t heureFinMaxPreconisee_p,
                                   boost::program_options::variables_map const & argv_p) {
    vector<int> sol_l = contextAlg_p.getCurrentSol();

    /* "ContextAlg, cette solution est peut etre mieux que ce que tu connais, 
     * mais peut etre pas. Verifie le, et met toi a jour si c'est le cas"
     */
    if ( contextAlg_p.checkCompletAndMajBestSol(sol_l, true) ){
        LOG(USELESS) << "La solution initialement sur le contextALG envoie du pate !" << endl;
    }

    cerr << "initialisation des objets" << endl;
    Checker checker_l(&contextAlg_p);
    EvaluationSystemALG evaluation_l;
    evaluation_l.setpContext(&contextAlg_p);
    ConstraintSystemALG constraints_l;
    constraints_l.setpContext(&contextAlg_p);
    OPPMSpaceALG * pInitialSpace_l = new OPPMSpaceALG;
    pInitialSpace_l->setpConstraintSystem(&constraints_l);
    pInitialSpace_l->setpEvaluationSystem(&evaluation_l);
    pInitialSpace_l->setpContext(&contextAlg_p);
    
    cerr << "construction de l'arbre" << endl;
    MonteCarloTreeSearchALG mcts_l;
    TreeALG< TreeSimpleImplALG<NodeContentALG> > tree_l;
    mcts_l.setpTree(&tree_l);
    mcts_l.setpInitialSpace(pInitialSpace_l);
    
    cerr << "lancement de la methode de recherche arborescente" << endl;
    SolutionALG * pSolution_l = mcts_l.search();
    

    /* On souhaite que la prochaine strategie (s'il y en a une) considere comme solution courante la derniere qu'on a considere
     * (cette strategie pourra, si elle le desire, ignorer cette solution initial qu'on lui fourni)
     */

    contextAlg_p.setCurrentSol(sol_l);
    return contextAlg_p;
}
