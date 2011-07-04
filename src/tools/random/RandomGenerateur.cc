#include "tools/random/RandomGenerateur.hh"
#include "tools/random/RandomCore.hh"
#include "tools/random/RandomCoreImpl.hh"
#include <map>
#include <cassert>
#include <cmath>
#include <iostream>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;
#define PI 3.14159265

RandomGenerateur* RandomGenerateur::mySingleton_m(0);

RandomGenerateur::RandomGenerateur() :
  core_m(new RandomCoreImpl()), //Implantation par defaut
  seed_m(0)
  {
    core_m->setSeed(seed_m);
  }

RandomGenerateur::~RandomGenerateur(){
  delete core_m;
  mySingleton_m = 0;
}

void RandomGenerateur::cleanSingleton(){
  //Le destructeur se charge de nettoyer ce qu'il faut
  delete mySingleton_m;
  mySingleton_m = 0;
}

RandomGenerateur* RandomGenerateur::getInstance(){
  if ( ! mySingleton_m ){
    mySingleton_m = new RandomGenerateur();
  }

  return mySingleton_m;
}

void RandomGenerateur::setSeed(long seed_p){
  seed_m = seed_p;
  core_m->setSeed(seed_m);
}

void RandomGenerateur::setRandomCore(RandomCore* core_p, bool reinitSeed_p){
  delete core_m;
  core_m = core_p;
  if ( reinitSeed_p ){
    core_m->setSeed(seed_m);
  }
}

double RandomGenerateur::generateUniformeDouble(double min_p, double max_p){
  assert(min_p < max_p);
  double x_l = core_m->generate();
  return (max_p - min_p) * x_l + min_p;
}

int RandomGenerateur::generateUniformeInt(int min_p, int max_p){
  assert(min_p < max_p);
  return floor( generateUniformeDouble(min_p, max_p) );
}

/* Algo en O(k_p) en temps et en espace :)
 * (on memorise les nombres deja pioches, et on substitue si on pioche plusieurs fois le meme x_l)
 */
vector<int> RandomGenerateur::tirageAleatoireSansRemise(int k_p, int n_p){
  assert(k_p <= n_p);
  vector<int> result_l;
  result_l.reserve(k_p);
  unordered_map<int, int> dejaTires_l;

  for ( int nbIt_l=0 ; nbIt_l < k_p ;  nbIt_l++ ){
    int x_l = generateUniformeInt(0, n_p-nbIt_l);
    unordered_map<int, int>::iterator it_l = dejaTires_l.find(x_l);

    //Si on a deja tire ce x_l
    if ( it_l != dejaTires_l.end() ){
      result_l.push_back(it_l->second);
    } else {
      result_l.push_back(x_l);
    }

    //Maj de la memoire des elements deja pioches
    unordered_map<int, int>::iterator it2_l = dejaTires_l.find(n_p-nbIt_l-1);
    if ( it2_l == dejaTires_l.end() ){      
      dejaTires_l[x_l] = n_p - nbIt_l - 1;
    } else {
      dejaTires_l[x_l] = it2_l->second;
    }
  }

  return result_l;
}

/* Generation suivant la methode de Box Muller
 */
double RandomGenerateur::generateNormale(double mu_p, double sigma_p){
  static bool oneInStock_l(false);
  static double stock_l(0);

  if ( ! oneInStock_l ){
    double x1_l = core_m->generate();
    double x2_l = core_m->generate();

    double coef_l = sqrt(-2*log(x1_l));
    double argTrigo_l = 2*PI*x2_l;


    double res_l = coef_l * cos(argTrigo_l);
    stock_l = coef_l * sin(argTrigo_l);
    oneInStock_l = true;
    return mu_p + res_l*sigma_p;
  } else {
    oneInStock_l = false;
    return mu_p + stock_l*sigma_p;
  }
}

double RandomGenerateur::inverseProbNorm(double& u) const{
    double r;    
    double x;

    x=u-0.5;
    if (fabs(x)<0.42)
    {
        r=x*x;
        r=x*((( -25.44106049637*r + 41.39119773534)*r -18.61500062529)*r +2.50662823884) /
            ((((3.13082909833*r - 21.06224101826)*r + 23.08336743743)*r -8.47351093090)*r + 1.0);
        return r;
    }

    r=u;
    if (x>0.0) r=1.0-u;
    r=log(-log(r));
    r=0.3374754822726147+r*(0.9761690190917186+r*(0.1607979714918209+r*(0.0276438810333863+r*(0.0038405729373609+
                        r*(0.0003951896511919+r*(0.0000321767881768+r*(0.0000002888167364+r*0.0000003960315187)))))));
    if (x<0.0) r=-r;

    return r;
}
