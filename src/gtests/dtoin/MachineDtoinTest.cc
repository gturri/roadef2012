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

#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, MachineDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataMachine(&context_l);

    ASSERT_EQ(context_l.getNbMachines(), 4);
    ASSERT_EQ(context_l.getNbLocations(), 3);
    ASSERT_EQ(context_l.getNbNeighborhoods(), 2);

    //Machine 0
    EXPECT_EQ(context_l.getMachine(0)->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getNeighborhood()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getLocation()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getCapa(0), 30);
    EXPECT_EQ(context_l.getMachine(0)->getCapa(1), 400);
    EXPECT_EQ(context_l.getMachine(0)->getSafetyCapa(0), 16);
    EXPECT_EQ(context_l.getMachine(0)->getSafetyCapa(1), 80);
    
    //Machine 1
    EXPECT_EQ(context_l.getMachine(1)->getId(), 1);
    EXPECT_EQ(context_l.getMachine(1)->getNeighborhood()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(1)->getLocation()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(1)->getCapa(0), 10);
    EXPECT_EQ(context_l.getMachine(1)->getCapa(1), 240);
    EXPECT_EQ(context_l.getMachine(1)->getSafetyCapa(0), 8);
    EXPECT_EQ(context_l.getMachine(1)->getSafetyCapa(1), 160);

    //Machine 2
    EXPECT_EQ(context_l.getMachine(2)->getId(), 2);
    EXPECT_EQ(context_l.getMachine(2)->getNeighborhood()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(2)->getLocation()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(2)->getCapa(0), 15);
    EXPECT_EQ(context_l.getMachine(2)->getCapa(1), 100);
    EXPECT_EQ(context_l.getMachine(2)->getSafetyCapa(0), 12);
    EXPECT_EQ(context_l.getMachine(2)->getSafetyCapa(1), 80);

    //Machine 3
    EXPECT_EQ(context_l.getMachine(3)->getId(), 3);
    EXPECT_EQ(context_l.getMachine(3)->getNeighborhood()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(3)->getLocation()->getId(), 2);
    EXPECT_EQ(context_l.getMachine(3)->getCapa(0), 10);
    EXPECT_EQ(context_l.getMachine(3)->getCapa(1), 100);
    EXPECT_EQ(context_l.getMachine(3)->getSafetyCapa(0), 8);
    EXPECT_EQ(context_l.getMachine(3)->getSafetyCapa(1), 80);

    //MMC
    MMCBO* pMMC_l = context_l.getMMCBO();
    EXPECT_EQ(pMMC_l->getCost(0, 0), 0);
    EXPECT_EQ(pMMC_l->getCost(0, 1), 1);
    EXPECT_EQ(pMMC_l->getCost(0, 2), 4);
    EXPECT_EQ(pMMC_l->getCost(0, 3), 5);
    EXPECT_EQ(pMMC_l->getCost(1, 0), 1);
    EXPECT_EQ(pMMC_l->getCost(1, 1), 0);
    EXPECT_EQ(pMMC_l->getCost(1, 2), 3);
    EXPECT_EQ(pMMC_l->getCost(1, 3), 4);
    EXPECT_EQ(pMMC_l->getCost(2, 0), 4);
    EXPECT_EQ(pMMC_l->getCost(2, 1), 3);
    EXPECT_EQ(pMMC_l->getCost(2, 2), 0);
    EXPECT_EQ(pMMC_l->getCost(2, 3), 2);
    EXPECT_EQ(pMMC_l->getCost(3, 0), 5);
    EXPECT_EQ(pMMC_l->getCost(3, 1), 4);
    EXPECT_EQ(pMMC_l->getCost(3, 2), 2);
    EXPECT_EQ(pMMC_l->getCost(3, 3), 0);
}
