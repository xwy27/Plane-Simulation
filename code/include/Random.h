#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <climits>
#include <cmath>
#include <ctime>
using namespace std;

enum Error_code {success, overflow, underflow, fail};

class Random {
private:
    int reseed();
    //  Re-randomize the seed.
    int seed, 
    multiplier, add_on; //  constants for use in arithmetic operations.
public:
    Random(bool pseudo = true);
    //  Declare random-number genration methods here.
    double random_real();
    int random_integer(int low, int high);
    int poisson(double mean);
    
};



#endif
