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

