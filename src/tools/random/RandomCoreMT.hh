#ifndef RANDOM_CORE_MERSENNE_TWISTER
#define RANDOM_CORE_MERSENNE_TWISTER
#include "tools/random/RandomCore.hh"
#include <iostream>
#include <cmath>

class RandomCoreMT : public RandomCore {


    /* Period parameters */  
    static const int N; // 624
    static const int M; // 397
    static const int MATRIX_A;   // 0x9908b0dfUL   /* constant vector a */
    static const int UPPER_MASK; // 0x80000000UL /* most significant w-r bits */
    static const int LOWER_MASK;     //  0x7fffffffUL /* least significant r bits */
    static int NBinst;


    static unsigned long * mt;//[N]; /* the array for the state vector  */
    static int mti;// =N+1; /* mti==N+1 means mt[N] is not initialized */
    void init_genrand(unsigned long s) const;
    void init_by_array(unsigned long init_key[], int key_length) const;


    public:
    RandomCoreMT(unsigned long s=0) {init_genrand(s);}
    RandomCoreMT(unsigned long init_key[], int key_length){init_by_array(init_key,key_length);}

    unsigned long genrand_int32(void) const;
    long genrand_int31(void) const;
    double genrand_real1(void) const;
    double genrand_real2(void) const;
    double genrand_real3(void) const;
    double genrand_res53(void) const;
    double simule() const;
    double simule(double min = 0., double max = 1.) const;
    int simuleInt(int min = 0, int max = 10) const;
    
    void setSeed(long seed_p);
    virtual double generate();

    // Par ce destructeur on s'assure que le tableau dynamique ne sera detruit que lorsqu'il n'y aura plus 
    // qu'une instance courante de loi RandomCoreMT.  
    ~RandomCoreMT(){NBinst--; if(!NBinst) delete[] mt;}
};
#endif
