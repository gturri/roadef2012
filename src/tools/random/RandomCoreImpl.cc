#include "tools/random/RandomCoreImpl.hh"
#include <cstdlib>


void RandomCoreImpl::setSeed(long seed_p){
  srand(seed_p);
}

double RandomCoreImpl::generate(){
  double x_l = rand();
  return x_l / ( (double) RAND_MAX + 1); //Le cast en double evite l'overflow du int
}
