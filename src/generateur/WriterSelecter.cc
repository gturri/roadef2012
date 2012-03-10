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

#include "generateur/WriterSelecter.hh"
#include "dtoout/InstanceWriterDtoout.hh"
#include "dtoout/InstanceWriterHumanReadable.hh"
#include "tools/Log.hh"

shared_ptr<InstanceWriterInterface> WriterSelecter::getWriter(const string& writer_p){
    shared_ptr<InstanceWriterInterface> result_l(new InstanceWriterDtoout);

    if ( writer_p == "human" ){
        LOG(DEBUG) << "Ecriture de l'instance via un 'human readable writer'" << endl;
        result_l = shared_ptr<InstanceWriterInterface>(new InstanceWriterHumanReadable);
    } else {
        LOG(DEBUG) << "Ecriture de l'instance via le writer officiel (choix par defaut)" << endl;
    }

    return result_l;
}
