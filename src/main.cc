#define TEAM_ID 666 /* TODO : completer quand on sera inscrit et qu'on aura notre identifiant d'equipe */
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Log.hh"
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
        InstanceReaderDtoin reader_l;
        ContextBO context_l = reader_l.read(instance_filename_l);
        SolutionDtoin::read(original_solution_filename_l, &context_l);
        InstanceWriterDtoout writer_l;
        writer_l.write(&context_l, "outfile.txt");
    } catch (string s_l){
        LOG(ERREUR) << "Levee de l'exception : " << s_l << endl;
    }

    return 0;
}





