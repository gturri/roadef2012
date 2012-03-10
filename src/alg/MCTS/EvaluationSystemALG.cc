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

#include "EvaluationSystemALG.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "tools/Checker.hh"

#include "tools/Log.hh"
#include <assert.h>

EvaluationSystemALG::EvaluationSystemALG()
: pContext_m(0)
{
    
}

EvaluationSystemALG::~EvaluationSystemALG()
{
}

void EvaluationSystemALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * EvaluationSystemALG::getpContext() const
{
    return pContext_m;
}

double EvaluationSystemALG::evaluate(ExplicitRepresentation const & solution_p)
{   
    double value_l = 0.0;
    size_t size_l = solution_p.size();
    int nbMachines = pContext_m->getContextBO()->getNbMachines();
    for(size_t i_l = 0; i_l < size_l; ++i_l)
    {
        value_l += solution_p[i_l];
    }
    value_l /= size_l;
    value_l /= nbMachines - 1;
    
    LOG(USELESS) << "On evalue la solution a " << value_l 
                 << " avec " << size_l 
                 << " process et " << nbMachines << " machines" << std::endl;

    if (value_l < 0) {
        value_l = 0;
    }

    assert(0 <= value_l && value_l <= 1);

    return value_l;
}
