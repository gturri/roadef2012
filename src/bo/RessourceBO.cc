#include "bo/RessourceBO.hh"


RessourceBO::RessourceBO(int id_p, bool isTransient_p, int loadCost_p) :
    id_m(id_p),
    isTransient_m(isTransient_p),
    loadCost_m(loadCost_p)
{}

int RessourceBO::getId() const{
    return id_m;
}

bool RessourceBO::isTransient() const{
    return isTransient_m;
}

int RessourceBO::getLoadCost() const{
    return loadCost_m;
}
