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

#include "ConstraintSystemALG.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"

ConstraintSystemALG::ConstraintSystemALG()
: pContext_m(0)
{
    
}

ConstraintSystemALG::~ConstraintSystemALG()
{
}

void ConstraintSystemALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * ConstraintSystemALG::getpContext() const
{
    return pContext_m;
}

ConstraintSystemALG::MachinePool ConstraintSystemALG::getLegalMachinePool(ProcessId process_l) const
{
    ConstraintSystemALG::MachinePool return_l;
    
    int nbMachines_l = pContext_m->getContextBO()->getNbMachines();
    
    for(int i_l = 0; i_l < nbMachines_l; ++i_l)
    {
        return_l.push_back(i_l);
    }
    
    return return_l;
}

void ConstraintSystemALG::unassign(ProcessId, MachineId)
{
    
}

void ConstraintSystemALG::assign(ProcessId,MachineId)
{
    
}


void ConstraintSystemALG::filter(ProcessPool & processPool_p) const
{
    
}

void ConstraintSystemALG::filter( ProcessId const & process_p, 
                                  MachinePool & machinePool_p) const
{
    
}
