#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"

ContextBO::~ContextBO(){
    for ( vector<RessourceBO*>::iterator it_l=ressources_m.begin() ; it_l != ressources_m.end() ; it_l++ ){
        delete *it_l;
    }
}

void ContextBO::addRessource(RessourceBO* pRess_p){
    ressources_m.push_back(pRess_p);
}

int ContextBO::getNbRessources() const{
    return ressources_m.size();
}

RessourceBO* ContextBO::getRessource(int id_p) const{
    return ressources_m[id_p];
}

