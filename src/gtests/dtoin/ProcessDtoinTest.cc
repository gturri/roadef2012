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

#include "gtests/dtoin/TestDtoinHelper.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/ServiceBO.hh"
#include <gtest/gtest.h>

TEST(dtoin, ProcessDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataService(&context_l);
    TestDtoinHelper::loadTestDataProcess(&context_l);

    ASSERT_EQ(context_l.getNbProcesses(), 3);
    EXPECT_EQ(context_l.getProcess(0)->getId(), 0);
    EXPECT_EQ(context_l.getProcess(0)->getService(), context_l.getService(0));
    EXPECT_EQ(context_l.getProcess(0)->getRequirement(0), 12);
    EXPECT_EQ(context_l.getProcess(0)->getRequirement(1), 10);
    EXPECT_EQ(context_l.getProcess(0)->getPMC(), 1000);

    EXPECT_EQ(context_l.getProcess(1)->getId(), 1);
    EXPECT_EQ(context_l.getProcess(1)->getService(), context_l.getService(0));
    EXPECT_EQ(context_l.getProcess(1)->getRequirement(0), 10);
    EXPECT_EQ(context_l.getProcess(1)->getRequirement(1), 20);
    EXPECT_EQ(context_l.getProcess(1)->getPMC(), 100);

    EXPECT_EQ(context_l.getProcess(2)->getId(), 2);
    EXPECT_EQ(context_l.getProcess(2)->getService(), context_l.getService(1));
    EXPECT_EQ(context_l.getProcess(2)->getRequirement(0), 6);
    EXPECT_EQ(context_l.getProcess(2)->getRequirement(1), 200);
    EXPECT_EQ(context_l.getProcess(2)->getPMC(), 1);

    ASSERT_EQ(context_l.getService(0)->getNbProcesses(), 2);
    EXPECT_TRUE(context_l.getService(0)->containsProcess(0));
    EXPECT_TRUE(context_l.getService(0)->containsProcess(1));
    EXPECT_FALSE(context_l.getService(0)->containsProcess(2));

    ASSERT_EQ(context_l.getService(1)->getNbProcesses(), 1);
    EXPECT_FALSE(context_l.getService(1)->containsProcess(0));
    EXPECT_FALSE(context_l.getService(1)->containsProcess(1));
    EXPECT_TRUE(context_l.getService(1)->containsProcess(2));
}
