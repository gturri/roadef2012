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
