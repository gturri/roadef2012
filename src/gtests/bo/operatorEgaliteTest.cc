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

#include "bo/BalanceCostBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
using namespace boost;

/* Les operator== ne sont en fait pas trivial (en particulier parce que les
 * unordered_set ne presentent pas eux meme cet operator). D'ou ces tests.
 * (qui, de prime abord, pourraient ressembler a une tentative vaine de 100pcent
 * coverage de fanatique...)
 */

TEST(operatorEgalite, BalanceCostBO){
    RessourceBO ress11_l(0, 1, 10), ress12_l(1, 0, 5), ress13_l(2, 1, 6);
    RessourceBO ress21_l(0, 1, 10), ress22_l(1, 0, 5);
    BalanceCostBO bc1_l(&ress11_l, &ress12_l, 3, 6),
                  bc2_l(&ress21_l, &ress22_l, 3, 6),
                  bc3_l(&ress11_l, &ress13_l, 3, 6),
                  bc4_l(&ress11_l, &ress12_l, 2, 5);

    EXPECT_TRUE(bc1_l == bc2_l);
    EXPECT_FALSE(bc1_l != bc2_l);
    EXPECT_FALSE(bc1_l == bc3_l);
    EXPECT_TRUE(bc1_l != bc3_l);
    EXPECT_FALSE(bc1_l == bc4_l);
    EXPECT_TRUE(bc1_l != bc4_l);
}

TEST(operatorEgalite, LocationBO){
    LocationBO loc11_l(0), loc12_l(1),
               loc21_l(0), loc12Trick_l(1);
    loc11_l.addMachine(3);
    loc21_l.addMachine(3);
    loc12_l.addMachine(0);
    loc12_l.addMachine(1);
    loc12Trick_l.addMachine(0);
    loc12Trick_l.addMachine(2);

    EXPECT_TRUE(loc11_l == loc21_l);
    EXPECT_FALSE(loc11_l != loc21_l);
    EXPECT_FALSE(loc12_l == loc12Trick_l);
    EXPECT_TRUE(loc12_l != loc12Trick_l);
}

TEST(operatorEgalite, MMCBO){
    vector<vector<int> > costs1_l(2, vector<int>(2, 0)),
        costs2_l(2, vector<int>(2, 0));
    costs1_l[1][0] = 2;
    costs2_l[0][1] = 3;
    MMCBO mmc11_l(costs1_l), mmc12_l(costs2_l), mmc21_l(costs1_l);
    EXPECT_TRUE(mmc11_l == mmc21_l);
    EXPECT_FALSE(mmc11_l != mmc21_l);
    EXPECT_FALSE(mmc11_l == mmc12_l);
    EXPECT_TRUE(mmc11_l != mmc12_l);
}

TEST(operatorEgalite, MachineBO){
    LocationBO loc1_l(0), loc2_l(1);
    NeighborhoodBO neigh1_l(0), neigh2_l(1);
    vector<int> capa1_l, capa2_l, safetyCapa1_l, safetyCapa2_l;
    capa1_l.push_back(0);
    capa2_l.push_back(1);
    safetyCapa1_l.push_back(0);
    safetyCapa2_l.push_back(1);

    MachineBO etalon_l(0, &loc1_l, &neigh1_l, capa1_l, safetyCapa1_l),
              egal_l(0, &loc1_l, &neigh1_l, capa1_l, safetyCapa1_l);
    vector<shared_ptr<MachineBO> > vpInstancesDiff_l;
    vpInstancesDiff_l.push_back(shared_ptr<MachineBO>(new MachineBO(1, &loc1_l, &neigh1_l, capa1_l, safetyCapa1_l)));
    vpInstancesDiff_l.push_back(shared_ptr<MachineBO>(new MachineBO(0, &loc2_l, &neigh1_l, capa1_l, safetyCapa1_l)));
    vpInstancesDiff_l.push_back(shared_ptr<MachineBO>(new MachineBO(0, &loc1_l, &neigh2_l, capa1_l, safetyCapa1_l)));
    vpInstancesDiff_l.push_back(shared_ptr<MachineBO>(new MachineBO(0, &loc1_l, &neigh1_l, capa2_l, safetyCapa1_l)));
    vpInstancesDiff_l.push_back(shared_ptr<MachineBO>(new MachineBO(0, &loc1_l, &neigh1_l, capa1_l, safetyCapa2_l)));

    EXPECT_TRUE(etalon_l == egal_l);
    EXPECT_FALSE(etalon_l != egal_l);

    BOOST_FOREACH(shared_ptr<MachineBO> pMachine_l, vpInstancesDiff_l){
        EXPECT_FALSE(etalon_l == *pMachine_l );
        EXPECT_TRUE(etalon_l != *pMachine_l);
    }
}

TEST(operatorEgalite, NeighborhoodBO){
    NeighborhoodBO n11_l(0), n12_l(1),
                   n21_l(0), n22_l(1);
    n11_l.addMachine(3);
    n21_l.addMachine(3);
    n12_l.addMachine(1); n12_l.addMachine(2);
    n12_l.addMachine(1); n12_l.addMachine(3);

    EXPECT_TRUE(n11_l == n21_l);
    EXPECT_FALSE(n11_l != n21_l);
    EXPECT_FALSE(n12_l == n22_l);
    EXPECT_TRUE(n12_l != n22_l);
}

TEST(operatorEgalite, ProcessBO){
    unordered_set<int> sDummy_l;
    vector<int> vDummy_l;
    LocationBO loc_l(0);
    NeighborhoodBO neigh_l(0);
    ServiceBO service1_l(0, 0, sDummy_l), service2_l(1, 0, sDummy_l);
    MachineBO machine1_l(0, &loc_l, &neigh_l, vDummy_l, vDummy_l), machine2_l(1, &loc_l, &neigh_l, vDummy_l, vDummy_l);
    vector<int> vRequirements1_l(1, 0), vRequirements2_l(1, 1);

    ProcessBO etalon_l(0, &service1_l, vRequirements1_l, 1),
             egal_l(0, &service1_l, vRequirements1_l, 1);
    etalon_l.setMachineInit(&machine1_l);
    egal_l.setMachineInit(&machine1_l);

    vector<shared_ptr<ProcessBO> > vpDiff_l;
    vpDiff_l.push_back(shared_ptr<ProcessBO>(new ProcessBO(1, &service1_l, vRequirements1_l, 1)));
    vpDiff_l.back()->setMachineInit(&machine1_l);
    vpDiff_l.push_back(shared_ptr<ProcessBO>(new ProcessBO(0, &service2_l, vRequirements1_l, 1)));
    vpDiff_l.back()->setMachineInit(&machine1_l);
    vpDiff_l.push_back(shared_ptr<ProcessBO>(new ProcessBO(0, &service1_l, vRequirements2_l, 1)));
    vpDiff_l.back()->setMachineInit(&machine1_l);
    vpDiff_l.push_back(shared_ptr<ProcessBO>(new ProcessBO(0, &service1_l, vRequirements1_l, 2)));
    vpDiff_l.back()->setMachineInit(&machine1_l);
    vpDiff_l.push_back(shared_ptr<ProcessBO>(new ProcessBO(0, &service1_l, vRequirements1_l, 1)));
    vpDiff_l.back()->setMachineInit(&machine2_l);

    BOOST_FOREACH(shared_ptr<ProcessBO> pProcess_l, vpDiff_l){
        EXPECT_FALSE(*pProcess_l == etalon_l);
        EXPECT_TRUE(*pProcess_l != etalon_l);
    }
}

TEST(operatorEgalite, RessourceBO){
    RessourceBO rEtalon_l(0, 1, 10),
                rEgal_l(0, 1, 10),
                rId_l(1, 1, 10),
                rTransient_l(0, 0, 10),
                rLCost_l(0, 1, 9);

    EXPECT_TRUE(rEtalon_l == rEgal_l);
    EXPECT_FALSE(rEtalon_l != rEgal_l);
    EXPECT_FALSE(rEtalon_l == rId_l);
    EXPECT_TRUE(rEtalon_l != rId_l);
    EXPECT_FALSE(rEtalon_l == rTransient_l);
    EXPECT_TRUE(rEtalon_l != rTransient_l);
    EXPECT_FALSE(rEtalon_l == rLCost_l);
    EXPECT_TRUE(rEtalon_l != rLCost_l);
}

TEST(operatorEgalite, ServiceBO){
    unordered_set<int> sDep_l, sDep2_l;
    sDep_l.insert(1);
    sDep2_l.insert(1); sDep2_l.insert(2);

    ServiceBO serviceEtalon_l(0, 2, sDep_l),
              serviceEgal_l(0, 2, sDep_l),
              serviceId_l(1, 2, sDep_l),
              serviceSpread_l(0, 3, sDep_l),
              serviceDep_l(0, 2, sDep2_l);

    EXPECT_TRUE(serviceEtalon_l == serviceEgal_l);
    EXPECT_FALSE(serviceEtalon_l != serviceEgal_l);
    EXPECT_FALSE(serviceEtalon_l == serviceId_l);
    EXPECT_TRUE(serviceEtalon_l != serviceId_l);
    EXPECT_FALSE(serviceEtalon_l == serviceSpread_l);
    EXPECT_TRUE(serviceEtalon_l != serviceSpread_l);
    EXPECT_FALSE(serviceEtalon_l == serviceDep_l);
    EXPECT_TRUE(serviceEtalon_l != serviceDep_l);
}
