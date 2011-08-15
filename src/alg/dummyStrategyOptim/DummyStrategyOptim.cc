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
            bool bestSolMaj_l = contextAlg_p.checkRapideAndMajBestSol(sol_l, scoreApres_l);

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
