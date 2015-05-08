
#include "stdafx.h"
//#include <stdarg.h>
//#include <string>
//#include <iostream>					// for cout etc.
//#include <vector>					// for vector class
//#include <string>					// for string class
//#include <algorithm>				// for sort algorithm
//#include <time.h>					// for random seed
//#include <math.h>					// for abs()
#include "MiscHeader.h"


#pragma warning(disable:4786)		// disable debug warning


//enum Selection { selectionDefault = 0 , RWS = 1 , SUS = 2 };
//enum Mutation { mutateDefault = 0, TwoPoint = 1  };


//#define GA_MUTATIONRATE	0.25f		// mutation rate
//#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
//#define GA_TARGET		std::string("Hello world!")
//#define GA_MAX_AGE		10

using namespace std;				// polluting global namespace, but hey...

extern int iteratorOfRuns; 

//
//struct ga_struct 
//{
//	string str;						// the string
//	unsigned int fitness;			// its fitness
//	int age;
//};
//
//typedef vector<ga_struct> ga_vector;// for brevity



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

typedef vector<ga_struct> ga_vector;// for brevity





class strings {

	int GA_POPSIZE;
	double GA_ELITRATE;
	int GA_MAXITER;
	int migrationFromEachIslands;
	int selection;
	int survivability;
	bool firstTimeToInitiatePopulation;
	bool firstTimeToRunSuS;
	int FitnessSum;
	int stepToTake;
	int indexByFitness;
	int fitnessMax;
	int fitnessMin;
	ga_vector pop_alpha, pop_beta;
	ga_vector *population, *buffer;


public:

	/*

	selection:	
	0 - default
	1 - RWS
	2 - SUS

	survivability:
	0 - No aging default
	1 - Default aging ( "taking" the next in line)
	1 - GENITOR

	*/
	strings(){
		GA_POPSIZE = 2000;
		GA_ELITRATE = 0.15f;
		GA_MAXITER = 16242;
		selection = 0;
		survivability = 0;
		FitnessSum = 0;
		indexByFitness = 0;
		firstTimeToInitiatePopulation = true;
		firstTimeToRunSuS = true;
		fitnessMin=10000;
		fitnessMax=0;
	}

	void initialize(int selection, int survivability, int populationPerIsland, double elitismeRate, int epocLength, int migrationFromEachIslands){

		this->GA_POPSIZE = populationPerIsland;
		GA_ELITRATE = elitismeRate;
		GA_MAXITER = epocLength;
		this->migrationFromEachIslands = migrationFromEachIslands;
		this->selection = selection;
		this->survivability = survivability;		

		return;

	}


#pragma region Logic


	void init_population(ga_vector &population,
		ga_vector &buffer ) 
	{
		int tsize = GA_TARGET.size();

		for (int i=0; i<GA_POPSIZE; i++) {
			ga_struct citizen;

			citizen.age = 0;
			citizen.fitness = 0;
			citizen.str.erase();

			for (int j=0; j<tsize; j++)
				citizen.str += (rand() % 90) + 32;

			population.push_back(citizen);
		}

		buffer.resize(GA_POPSIZE);
	}

	void calc_fitness(ga_vector &population)
	{
		string target = GA_TARGET;
		int tsize = target.size();
		unsigned int fitness;

		for (int i=0; i<GA_POPSIZE; i++) {
			fitness = 0;
			for (int j=0; j<tsize; j++) {
				fitness += abs(int(population[i].str[j] - target[j]));
			}

			population[i].fitness = fitness;
		}
	}

	static bool fitness_sort(ga_struct x, ga_struct y) 
	{ return (x.fitness < y.fitness); }

	void sort_by_fitness(ga_vector &population)
	{ sort(population.begin(), population.end(), fitness_sort); }

	void elitism(ga_vector &population, 
		ga_vector &buffer, int esize )
	{
		int counterOfAgingReplacement = 1;
		for (int i=0; i<esize; i++) {
			buffer[i].str = population[i].str;
			buffer[i].fitness = population[i].fitness;
			buffer[i].age = population[i].age;


			if (buffer[i].age++ >= GA_MAX_AGE) {

				switch (survivability)
				{
				case 0:
					break;
				case 1:
					buffer[i].str = population[counterOfAgingReplacement + esize].str;
					buffer[i].fitness = population[counterOfAgingReplacement + esize].fitness;
					buffer[i].age = population[esize  +(counterOfAgingReplacement++)].age;
					break;
				default:
					break;
				}
			}
		}
	}

	void mutate(ga_struct &member)
	{
		int tsize = GA_TARGET.size();
		int ipos = rand() % tsize;
		int delta = (rand() % 90) + 32; 

		member.str[ipos] = ((member.str[ipos] + delta) % 122);
	}

	void calculateFitnessSum(){
		int RWSSum = 0;
		for (int j = 0; j < population->size();  j++)
		{
			if((*population)[j].fitness>fitnessMax){
				fitnessMax=(*population)[j].fitness;
			}
			if((*population)[j].fitness<fitnessMin){
				fitnessMin=(*population)[j].fitness;
			}
			RWSSum += (*population)[j].fitness;
		}

		this->FitnessSum = RWSSum;
	}
	int getIndexByRWS( )
	{
		long sum = 0;
		indexByFitness = rand() % (FitnessSum);
		for (int i = 0 ; i < population->size() ; i++)
		{
			if ( ( (sum + ((fitnessMax + fitnessMin)- (unsigned long )((*population)[i].fitness)) >= indexByFitness )) && (sum < indexByFitness)  )
				return i;
			sum +=(fitnessMax + fitnessMin)- (*population)[i].fitness;
		}
		return 0;
	}

	int getIndexBySUS(){


		if (firstTimeToRunSuS){ // If its first run of SUS we need to get random index, exactly as RWS
			firstTimeToRunSuS = false;
			return getIndexByRWS();
		}
		long sum = 0;
		indexByFitness = (indexByFitness + stepToTake) % FitnessSum;
		for (int i = 0 ; i < population->size() ; i++)
		{
			if ( ( (sum + ((fitnessMax + fitnessMin)-(unsigned long )((*population)[i].fitness))) >= indexByFitness ) && (sum < indexByFitness)  )
				return i;
			sum += (fitnessMax + fitnessMin)-(*population)[i].fitness;
		}
		return 0;

	}

	void mate(ga_vector &population, ga_vector &buffer)
	{
		int esize = GA_POPSIZE * GA_ELITRATE;
		int tsize = GA_TARGET.size(), spos, i1, i2;

		elitism(population, buffer, esize);
		calculateFitnessSum();
		stepToTake = (int)((double)FitnessSum / ( 2 * GA_POPSIZE * ( 1- GA_ELITRATE) ) );
		firstTimeToRunSuS = true;
		// Mate the rest
		for (int i=esize; i<GA_POPSIZE; i++) {

			switch (selection)
			{
			case 1:
				i1 = getIndexByRWS();
				i2 = getIndexByRWS();
				break;
			case 2:
				i1 = getIndexBySUS();
				i2 = getIndexBySUS();
				break;
			default:
				i1 = rand() % (GA_POPSIZE / 2);
				i2 = rand() % (GA_POPSIZE / 2);
				break;
			}

			spos = rand() % tsize;

			buffer[i].str = population[i1].str.substr(0, spos) + 
				population[i2].str.substr(spos, tsize - spos);
			buffer[i].age=0;

			if (rand() < GA_MUTATION) mutate(buffer[i]);
		}
	}

	void print_best(ga_vector &gav)
	{ cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl; }

	void swap(ga_vector *&population,
		ga_vector *&buffer)
	{ ga_vector *temp = population; population = buffer; buffer = temp; }


#pragma endregion logic



	bool run()
	{
		srand(unsigned(time(NULL)));

		if (firstTimeToInitiatePopulation){
			firstTimeToInitiatePopulation = false;
			init_population(pop_alpha, pop_beta);
			population = &pop_alpha;
			buffer = &pop_beta;
		}

		for (int i=0; i<GA_MAXITER; i++) {
			calc_fitness(*population);		// calculate fitness
			sort_by_fitness(*population);	// sort them
			cout << "it: " << iteratorOfRuns ++ << " -- ";
			print_best(*population);		// print the best one

			if ((*population)[0].fitness == 0) return true;

			mate(*population, *buffer);		// mate the population together
			swap(population, buffer);		// swap buffers
		}

		return false;
	}

	void SetForReplacment (ga_vector &citizensToAdd){

		if (citizensToAdd.capacity() < migrationFromEachIslands){

			cout << "There was an error in SetForReplacment, citizensToAdd.capacity: " << citizensToAdd.capacity() << endl << flush ;

			return;
		}
		for (int i = 0; i < migrationFromEachIslands; i++)
		{
			population->push_back(citizensToAdd[i]);
		}

		sort_by_fitness(*population);	// sort them

		print_best(*population);		// print the best one

	}


	ga_vector* getForReplacment () {

		ga_vector *temp = new ga_vector();
		for (int i = 0; i < migrationFromEachIslands; i++)
		{
			int ipos = rand() % (GA_POPSIZE - i);

			temp->push_back(population->at(ipos));

			population->erase(population -> begin () + ipos);

		}

		return temp;
	}

};
