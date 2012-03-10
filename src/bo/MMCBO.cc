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

#include "bo/MMCBO.hh"
#include "bo/MachineBO.hh"

MMCBO::MMCBO(const vector<vector<int> >& costs_p) :
    costs_m(costs_p)
{}

int MMCBO::getCost(MachineBO* from_p, MachineBO* to_p) const {
    return costs_m[from_p->getId()][to_p->getId()];
}

int MMCBO::getCost(int idxMachineFrom_p, int idxMachineTo_p) const{
    return costs_m[idxMachineFrom_p][idxMachineTo_p];
}

vector<int> MMCBO::getCosts(MachineBO* from_p) const{
    return costs_m[from_p->getId()];
}

bool MMCBO::operator==(const MMCBO& mmc_p) const{
    return costs_m == mmc_p.costs_m;
}

bool MMCBO::operator!=(const MMCBO& mmc_p) const{
    return !this->operator==(mmc_p);
}
