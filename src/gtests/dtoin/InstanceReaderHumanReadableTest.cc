#include "dtoin/InstanceReaderHumanReadable.hh"
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>
using namespace std;

//Fixture qui permet de d'acceder aux methode protected
class InstanceReaderHumanReadableFixture : public InstanceReaderHumanReadable, public testing::Test
{};

TEST_F(InstanceReaderHumanReadableFixture, getNextLine){
    ostringstream oss_l;
    string ligne1_l("Ma premiere ligne"),
           ligne2_l("seconde ligne");
    oss_l << ligne1_l << endl << " " <<  endl << ligne2_l;

    istringstream iss_l(oss_l.str());
    EXPECT_EQ(ligne1_l, getNextLine(iss_l));
    EXPECT_EQ(ligne2_l, getNextLine(iss_l));
    EXPECT_EQ("", getNextLine(iss_l));
    EXPECT_EQ("", getNextLine(iss_l));
}

TEST_F(InstanceReaderHumanReadableFixture, checkSectionTitle){
    vector<pair<string, string> > vLignesPourries_l;
    map<string, string> mLignesOk_l;

    mLignesOk_l["===== titreA ======"] = "titreA";
    mLignesOk_l["===== titreA ======"] = "TitreA";
    mLignesOk_l["=====TitreB====== "] = "titreB";
    vLignesPourries_l.push_back(make_pair("==== titre=====", "titre")); //Pas assez de = en tete
    vLignesPourries_l.push_back(make_pair("=====titre5=====", "titre5")); //contient un chiffre
    vLignesPourries_l.push_back(make_pair(" ===== mon titre====", "mon titre")); //contient une espace
    vLignesPourries_l.push_back(make_pair("=====titreC====", "titreD"));
    vLignesPourries_l.push_back(make_pair("=====titreC====", "titreA"));

    for ( map<string, string>::iterator it_l=mLignesOk_l.begin() ; it_l != mLignesOk_l.end() ; it_l++ ){
        EXPECT_NO_THROW(checkSectionTitle(it_l->first, it_l->second)) << it_l->first << " vs " << it_l->second;
    }
    for ( vector<pair<string, string> >::iterator it_l=vLignesPourries_l.begin() ; it_l != vLignesPourries_l.end() ; it_l++ ){
        EXPECT_ANY_THROW(checkSectionTitle(it_l->first, it_l->second)) << it_l->first << " vs " << it_l->second;
    }
}

TEST_F(InstanceReaderHumanReadableFixture, checkSubTitle){
    EXPECT_NO_THROW(checkSubTitle("====Ressource 1/666====", "Ressource", 1, 666));
    EXPECT_NO_THROW(checkSubTitle("==== macHine  3  / 7  ===", "MAchine", 3, 7)); //Limite de la permissivite
    EXPECT_ANY_THROW(checkSubTitle("===Ressource 1/666====", "Ressource", 1, 666));
    EXPECT_ANY_THROW(checkSubTitle("====Ressource 1/666====", "Machine", 1, 666));
    EXPECT_ANY_THROW(checkSubTitle("====Ressource 1/666====", "Ressource", 2, 666));
    EXPECT_ANY_THROW(checkSubTitle("====Ressource 1/666====", "Ressource", 1, 42));
}

TEST_F(InstanceReaderHumanReadableFixture, readQuantite){
    EXPECT_EQ(2, readQuantite("quantite : 2"));
    EXPECT_EQ(4, readQuantite("  quantite:  4  "));
    EXPECT_ANY_THROW(readQuantite("uantite : 4"));
    EXPECT_ANY_THROW(readQuantite("quantite : 4 2"));
    EXPECT_ANY_THROW(readQuantite("quantite 4"));
}

TEST_F(InstanceReaderHumanReadableFixture, readCarac){
    EXPECT_EQ(69, readCarac("  * myValue : 69", "myValue"));
    EXPECT_EQ(69, readCarac("  * myValue   :  69  ", "myvalue"));
    EXPECT_EQ(1337, readCarac(" * myValue : 1337", "myValue"));
    EXPECT_ANY_THROW(readCarac("  * myValue : 69", "myValu"));
    EXPECT_ANY_THROW(readCarac("  * myValue : ", "myValue"));
    EXPECT_ANY_THROW(readCarac("  * myValue : 42 37", "myValue"));
}

TEST_F(InstanceReaderHumanReadableFixture, readListe){
    vector<int> v1_l;
    v1_l.push_back(19); v1_l.push_back(85);
    EXPECT_EQ(v1_l, readListe("  * mesValos : 19 85", "mesvalos"));
    EXPECT_ANY_THROW(readListe("  * mesValos : 19 85", "myvalue"));
}

