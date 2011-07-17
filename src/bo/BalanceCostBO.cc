#include "bo/BalanceCostBO.hh"
#include "bo/RessourceBO.hh"

BalanceCostBO::BalanceCostBO(RessourceBO* pRess1_p, RessourceBO* pRess2_p, int target_p, int poids_p) :
    pRess1_m(pRess1_p),
    pRess2_m(pRess2_p),
    target_m(target_p),
    poids_m(poids_p)
{}

RessourceBO* BalanceCostBO::getRessource1() const{
    return pRess1_m;
}

RessourceBO* BalanceCostBO::getRessource2() const{
    return pRess2_m;
}

int BalanceCostBO::getTarget() const{
    return target_m;
}

int BalanceCostBO::getPoids() const{
    return poids_m;
}

bool BalanceCostBO::operator==(const BalanceCostBO& bc_p) const{
    return pRess1_m->getId() == bc_p.pRess1_m->getId()
        && pRess2_m->getId() == bc_p.pRess2_m->getId()
        && target_m == bc_p.target_m
        && poids_m == bc_p.poids_m;
}

bool BalanceCostBO::operator!=(const BalanceCostBO& bc_p) const {
    return !this->operator==(bc_p);
}

