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

#include "dtoout/InstanceWriterInterface.hh"
#include <fstream>
#include <sstream>

InstanceWriterInterface::~InstanceWriterInterface(){}

void InstanceWriterInterface::write(ContextBO const * pContextBO_p, const string& out_filename_p){
    ofstream ofs_p(out_filename_p.c_str());
    if ( ! ofs_p ){
        ostringstream oss_l;
        oss_l << "Impossible de dumper l'instance dans le fichier " << out_filename_p << endl;
        throw oss_l.str();
    }

    write(pContextBO_p, ofs_p);
}

void InstanceWriterInterface::write(ContextBO const * pContextBO_p, ostream& os_p){
    os_p << write(pContextBO_p);
}

string InstanceWriterInterface::write(ContextBO const * pContextBO_p){
    return writeOnString(pContextBO_p);
}
