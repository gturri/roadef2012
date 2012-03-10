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

#include "tools/Log.hh"
#include <boost/regex.hpp>
using namespace boost;
using namespace std;

vector<string> LogHelper::vLogStrLvl_g = LogHelper::buildLogLvl();

/* Ci dessous : duplication de code, car on "redefinit" les levels de log
 * Ceci s'explique par le fait que dans le .hh on s'adresse au preprocesseur,
 * et ici, au compilo.
 *
 * Et puis de toute facon, c'est pas un "tool" qui va etre appelle a subir
 * de grosses maintenances, donc je ne pense pas que se soit si genant...
 */
vector<string> LogHelper::buildLogLvl(){
    vector<string> result_l;
    result_l.push_back("USELESS");
    result_l.push_back("DEBUG");
    result_l.push_back("INFO");
    result_l.push_back("WARNING");
    result_l.push_back("ERREUR");
    result_l.push_back("WTF");

    return result_l;
}

string LogHelper::extractFilename(const string& path_p){
    const static regex regex_l("([[:alpha:].]*)\\z");
    smatch match_l;
    if ( regex_search(path_p, match_l, regex_l) ){
        return match_l[1];
    } else {
        return path_p;
    }
}
