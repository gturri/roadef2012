#ifndef RANDOMCOREIMPL
#define RANDOMCOREIMPL

#include "tools/random/RandomCore.hh"

/**
 * Implantation de #RandomCore simpliste sur basant sur rand() (et n'apportant que ses pietres performances stochastiques...)
 */
class RandomCoreImpl : public RandomCore {
  public:
    void setSeed(long seed_p);
    double generate();
};


#endif
