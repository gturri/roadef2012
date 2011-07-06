#include "dtoin/RessourceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include <fstream>
#include <gtest/gtest.h>
using namespace std;

TEST(RessourceDtoin, read){
    RessourceDtoin reader_l;
    ifstream ifs_l("../src/gtests/dtoin/ressourceDtoinTest.txt");
    if ( ! ifs_l ){
        cerr << "Impossible d'ouvrir ressourceDtoinTest.txt dans le test RessourceDtoin_read" << endl;
    }
    ContextBO context_l;

    reader_l.read(ifs_l, &context_l);
    EXPECT_EQ(context_l.getNbRessources(), 2);

    RessourceBO* ress1_l = context_l.getRessource(0);
    EXPECT_EQ(ress1_l->getId(), 0);
    EXPECT_TRUE(ress1_l->isTransient());
    EXPECT_EQ(ress1_l->getLoadCost(), 100);

    RessourceBO* ress2_l = context_l.getRessource(1);
    EXPECT_EQ(ress2_l->getId(), 1);
    EXPECT_FALSE(ress2_l->isTransient());
    EXPECT_EQ(ress2_l->getLoadCost(), 10);
}
