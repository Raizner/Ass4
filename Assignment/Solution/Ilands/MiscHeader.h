#ifndef HHHH
#define HHHH

#include <stdarg.h>
#include <string>
#include <iostream>					// for cout etc.
#include <vector>					// for vector class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()
#include "Stats.h"
#define NUMBER_OF_QUEENS 11
#define MAX_NUMBER_OF_ITEMS 28

#define GA_MUTATIONRATE	0.25f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("abcdefghijklmnopqrstuvwxyz")
#define GA_MAX_AGE		4


#define GA_MAX_BAG_WEIGHT 1000
#define NUMBER_OF_OBJECTS 35
#define NUMBER_OF_SACKS 4




using namespace std;				// polluting global namespace, but hey...

struct ga_struct 
{
	string str;						// the string
	int board[NUMBER_OF_QUEENS];						// the string
	unsigned int fitness;			// its fitness
	int age;
	int weight[NUMBER_OF_SACKS];
	int bag[NUMBER_OF_OBJECTS];
	unsigned int knapsackFitness[NUMBER_OF_SACKS];
};



#endif
