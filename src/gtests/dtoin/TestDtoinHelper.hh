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

#ifndef TESTDTOINHELPER_HH
#define TESTDTOINHELPER_HH

#include <string>
using namespace std;

class ContextBO;

class TestDtoinHelper {
    public:
        static void loadTestDataRessource(ContextBO* pContextBO_p);
        static void loadTestDataMachine(ContextBO* pContextBO_p);
        static void loadTestDataService(ContextBO* pContextBO_p);
        static void loadTestDataProcess(ContextBO* pContextBO_p);
        static void loadTestDataBalanceCost(ContextBO* pContextBO_p);
        static void loadTestDataPoids(ContextBO* pContextBO_p);
        static void loadTestDataSolInit(ContextBO* pContextBO_p);

    private:
        static string getMachineTestData();
        static string getRessourceTestData();
        static string getServiceTestData();
        static string getProcessTestData();
        static string getBalanceCostTestData();
        static string getPoidsTestData();
        static string getSolInitTestData();
};

#endif
