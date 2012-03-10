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

#include "dtoout/SolutionDtoout.hh"
#include <boost/thread.hpp>
#include <gtest/gtest.h>
using namespace boost;
using namespace boost::date_time;

TEST(SolutionDtoout, keepBestScore){
    SolutionDtoout::reinit("/dev/null");
    uint64_t score_l = 666;
    vector<int> sol_l(5);

    ASSERT_TRUE(SolutionDtoout::writeSol(sol_l, score_l));
    ASSERT_EQ(score_l, SolutionDtoout::getBestScore());
    ASSERT_EQ(sol_l, SolutionDtoout::getBestSol());
}

TEST(SolutionDtoout, writeOnlyIfBetterScore){
    SolutionDtoout::reinit("/dev/null");

    uint64_t score1_l = 1337;
    vector<int> sol1_l(1);
    uint64_t score2_l = 69;
    vector<int> sol2_l(2);
    uint64_t score3_l = 666;
    vector<int> sol3_l(3);

    ASSERT_TRUE(SolutionDtoout::writeSol(sol1_l, score1_l));
    ASSERT_TRUE(SolutionDtoout::writeSol(sol2_l, score2_l));
    ASSERT_FALSE(SolutionDtoout::writeSol(sol3_l, score3_l));

    ASSERT_EQ(score2_l, SolutionDtoout::getBestScore());
    ASSERT_EQ(sol2_l, SolutionDtoout::getBestSol());
}

TEST(SolutionDtoout, throwIfWrongFile){
    SolutionDtoout::reinit("/W/T/F.txt");
    ASSERT_ANY_THROW(SolutionDtoout::writeSol(vector<int>(), 42));
}

struct callableSolutionDtooutWrite {
    void operator()(const vector<int>& sol_p, int score_p){
        try {
            SolutionDtoout::writeSol(sol_p, score_p);
        } catch ( ... ) {
            //Rien : on s'attend a avoir une exception
        }
    }
};

TEST(SolutionDtoout, unlockIfWrongFile){
    SolutionDtoout::reinit("/W/T/F.txt");
    ASSERT_ANY_THROW(SolutionDtoout::writeSol(vector<int>(), 42));


    callableSolutionDtooutWrite call_l;
    thread thread_l(call_l, vector<int>(), 13);
    ASSERT_TRUE(thread_l.timed_join(boost::posix_time::millisec(3000)));

}
