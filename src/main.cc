#define TEAM_ID 666 /* TODO : completer quand on sera inscrit et qu'on aura notre identifiant d'equipe */
#include "alg/ContextALG.hh"
#include "alg/dummyStrategyOptim/DummyStrategyOptim.hh"
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Log.hh"
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

void usage()
{
    cout << "Options possibles :" << endl
        << "\t-t temps max du run (en secondes)" << endl
        << "\t-p instance_filename" << endl
        << "\t-i original_solution_filename" << endl
        << "\t-o new_solution_filename" << endl
        << "\t-n : option sans argument demandant l'affichage de l'id de l'equipe" << endl
        << "\t-s random_seed" << endl
        << "\t-h afficher cette aide" << endl;
}

int main(int argc, char **argv) {
    /* Debut de la (longue) partie qui lit et qui traite les arguments de la cmd line
     * (il peut etre malin de deporter cette partie dans une methode idoine,
     * voir, d'utiliser boost::program_option)
     */
    int time_limit_second_l(300);
    string instance_filename_l;
    string original_solution_filename_l;
    string new_solution_filename_l;
    bool send_name_l(false);
    int seed_l(0);
    bool helpWanted_l(false);


    while ((argc > 1) && (argv[1][0] == '-'))
    {
        switch (argv[1][1])
        {
            case 't' :
                {
                    istringstream iss_l(argv[2]);
                    iss_l >> time_limit_second_l;
                }
                break;
            case 'p' :
                instance_filename_l = argv[2];
                break;
            case 'i' :
                original_solution_filename_l = argv[2];
                break;
            case 'o' :
                new_solution_filename_l = argv[2];
                SolutionDtoout::setOutFileName(new_solution_filename_l);
                break;
            case 'n':
                send_name_l = true;
                argc++;
                argv--;
                break;
            case 's':
                {
                    istringstream iss_l(argv[2]);
                    iss_l >> seed_l;
                }
                break;
            case 'h':
            case '-':
                helpWanted_l = true;
                argc++;
                argv--;
                break;
            default : 
                usage();
                return -1;
        }
        --(--argc);
        ++(++argv);
    }

    LOG(INFO) << "temps limite : " << time_limit_second_l << " s" << endl
        << "instance file  : ./" << instance_filename_l << endl
        << "original sol : ./" << original_solution_filename_l << endl
        << "new sol : ./" << new_solution_filename_l << endl
        << "send our name : " << send_name_l << endl
        << "seed : " << seed_l << endl;

    if ( send_name_l ){
        cout << TEAM_ID << endl;
    }
    if ( helpWanted_l ){
        usage();
    }
    if ( instance_filename_l == "" ){
        return 0;
    }
    /* Fin de la lecture et du traitement des args de la cmd line
     */

    try {
        /* Lecture du fichier d'instance et de solution initiale
         */
        InstanceReaderDtoin reader_l;
        ContextBO contextBO_l = reader_l.read(instance_filename_l);
        SolutionDtoin::read(original_solution_filename_l, &contextBO_l);

        /* Lancement de la sequence d'optim.
         *
         * FIXME : Il serait pertinent de virer cette logique du main.
         * Plus precisement, il serait malin de creer une classe qui mange un ContextBO plus les donnees interessantes de la ligne de commande,
         * qui construit une sequence de StrategyOptim et qui l'execute
         *
         * En attendant, je me contente d'executer une unique StrategyOptim bidon
         * afin d'avoir une chaine complete
         */
        ContextALG contextALG_l(&contextBO_l);
        StrategyOptim* pStrategy_l = new DummyStrategyOptim();
        pStrategy_l->run(contextALG_l, time(0) + time_limit_second_l);
        delete pStrategy_l;

    } catch (string s_l){
        LOG(ERREUR) << "Levee de l'exception : " << s_l << endl;
    }

    return 0;
}





