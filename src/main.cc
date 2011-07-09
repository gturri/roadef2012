#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

void usage()
{
    cerr << "parametres incorrectes" << endl;
}

int main(int argc, char **argv) {
    int time_limit_second_l(300);
    string instance_filename_l;
    string original_solution_filename_l;
    string new_solution_filename_l;
    bool send_name_l(false);
    int seed_l(0);


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
                cout << "lecture de la graine : " << seed_l << endl;
                break;
            default : 
                usage();
                return -1;
        }
        --(--argc);
        ++(++argv);
    }

    cout << "temps limite : " << time_limit_second_l << " s" << endl
        << "instance file  : ./" << instance_filename_l << endl
        << "original sol : ./" << original_solution_filename_l << endl
        << "new sol : ./" << new_solution_filename_l << endl
        << "send our name : " << send_name_l << endl
        << "seed : " << seed_l << endl;

    ContextBO context_l = InstanceReaderDtoin::read(instance_filename_l);
    InstanceWriterDtoout::write(&context_l, "outfile.txt");

    return 0;
}





