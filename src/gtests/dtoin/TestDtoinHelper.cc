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
#include "dtoin/BalanceCostDtoin.hh"
#include "dtoin/MachineDtoin.hh"
#include "dtoin/PoidsDtoin.hh"
#include "dtoin/ProcessDtoin.hh"
#include "dtoin/RessourceDtoin.hh"
#include "dtoin/ServiceDtoin.hh"
#include "dtoin/SolutionDtoin.hh"
#include <sstream>
using namespace std;

void TestDtoinHelper::loadTestDataRessource(ContextBO* pContextBO_p){
    RessourceDtoin reader_l;
    istringstream iss_l(getRessourceTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataMachine(ContextBO* pContextBO_p){
    MachineDtoin reader_l;
    istringstream iss_l(getMachineTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataService(ContextBO* pContextBO_p){
    ServiceDtoin reader_l;
    istringstream iss_l(getServiceTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataProcess(ContextBO* pContextBO_p){
    ProcessDtoin reader_l;
    istringstream iss_l(getProcessTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataBalanceCost(ContextBO* pContextBO_p){
    BalanceCostDtoin reader_l;
    istringstream iss_l(getBalanceCostTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataPoids(ContextBO* pContextBO_p){
    PoidsDtoin reader_l;
    istringstream iss_l(getPoidsTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataSolInit(ContextBO* pContextBO_p){
    SolutionDtoin reader_l;
    istringstream iss_l(getSolInitTestData());
    reader_l.read(iss_l, pContextBO_p);
}

string TestDtoinHelper::getMachineTestData(){
    return string("4 \
 \
0 \
0 \
30 400 \
16 80 \
0 1 4 5 \
 \
0 \
0 \
10 240 \
8 160 \
1 0 3 4 \
 \
1 \
1 \
15 100 \
12 80 \
4 3 0 2 \
 \
1 \
2 \
10 100 \
8 80 \
5 4 2 0");
}

string TestDtoinHelper::getRessourceTestData(){
    return string("2 \
 \
1 \
100 \
 \
0 \
10");
}

string TestDtoinHelper::getServiceTestData(){
    return string("2 \
 \
2 \
0 \
 \
1 \
1 \
0 \
 \
3 \
0 \
12 10 \
1000 \
 \
0 \
10 20 \
100 \
 \
1 \
6 200 \
1");
}

string TestDtoinHelper::getProcessTestData(){
    return string("3 \
0 \
12 10 \
1000 \
\
0 \
10 20 \
100 \
\
1 \
6 200 \
1");
}

string TestDtoinHelper::getBalanceCostTestData(){
    return string("1 \
0 1 20 \
10");
}

string TestDtoinHelper::getPoidsTestData(){
    return string("1 \
10 \
100");
}

string TestDtoinHelper::getSolInitTestData(){
    return string("0 3 0");
}
