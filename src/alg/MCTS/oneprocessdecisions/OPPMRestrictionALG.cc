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

#include "OPPMRestrictionALG.hh"

#include "tools/Log.hh"

OPPMRestrictionALG::OPPMRestrictionALG( ProcessId target_p,
                                        MachinePool const & subset_p)
: target_m(target_p), pool_m()
{
    pool_m = RestrictedMachinePool(subset_p.begin(),subset_p.end());
}

OPPMRestrictionALG::~OPPMRestrictionALG() 
{
}

void OPPMRestrictionALG::filter(ProcessPool &) const
{
    return;
}

void OPPMRestrictionALG::filter( ProcessId const & process_p,
                                 MachinePool & allowAssignment_p) const
{
    if( process_p == target_m)
    {
        LOG(USELESS) << "On restreint pour le process " << process_p << std::endl;
        // A refaire : il existe un algo plus rapide si les listes sont triees
        MachinePool::iterator it_l = allowAssignment_p.begin();
        while (it_l != allowAssignment_p.end())
        {
            if ( pool_m.find(*it_l) == pool_m.end() )
            {
                it_l = allowAssignment_p.erase(it_l);
            }
            else
            {
                ++it_l;
            }
        }
    }
    else
    {
        return;
    }
}
