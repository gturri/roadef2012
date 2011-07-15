#include "bo/RessourceBO.hh"


RessourceBO::RessourceBO(int id_p, bool isTransient_p, int weightLoadCost_p) :
    id_m(id_p),
    isTransient_m(isTransient_p),
    weightLoadCost_m(weightLoadCost_p)
{}

int RessourceBO::getId() const{
    return id_m;
}

bool RessourceBO::isTransient() const{
    return isTransient_m;
}

int RessourceBO::getWeightLoadCost() const{
    return weightLoadCost_m;
}

bool RessourceBO::operator==(const RessourceBO& ress_l) const {
    return id_m == ress_l.id_m
        && isTransient_m == ress_l.isTransient_m
        && weightLoadCost_m == ress_l.weightLoadCost_m;
}

bool RessourceBO::operator!=(const RessourceBO& ress_l) const{
    return ! (this->operator==(ress_l));
}
