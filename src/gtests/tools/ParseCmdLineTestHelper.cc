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

#include "gtests/tools/ParseCmdLineTestHelper.hh"
#include <cassert>
#include <cstring>

ParseCmdLineTestHelper::ParseCmdLineTestHelper() :
    argv_m(0),
    argvCreated_m(false)
{}

ParseCmdLineTestHelper::~ParseCmdLineTestHelper(){
    if ( argvCreated_m ){
        for ( int idx_l=0 ; idx_l < argc() ; idx_l++ ){
            delete[] argv_m[idx_l];
        }
    }

    delete[] argv_m;
}

char** ParseCmdLineTestHelper::argv(){
    if ( ! argvCreated_m ){
        argvCreated_m = true;
        int nbOpt_l = argc();
        argv_m = new char*[nbOpt_l];

        argv_m[0] = new char[15];
        strcpy(argv_m[0], "nomBinaire");

        for ( int idx_l=0 ; idx_l < (int) options_m.size() ; idx_l++ ){
            argv_m[idx_l+1] = new char[options_m[idx_l].size() + 1];
            strcpy(argv_m[idx_l+1], options_m[idx_l].c_str());
        }
    }

    return argv_m;
}

int ParseCmdLineTestHelper::argc(){
    return options_m.size()+1;
}

void ParseCmdLineTestHelper::addCmdLineArg(const string& arg_p){
    assert(!argvCreated_m);
    options_m.push_back(arg_p);
}
