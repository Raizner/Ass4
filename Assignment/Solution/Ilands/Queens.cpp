// Genetic5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <stdarg.h>
//#include <string>
//#include <iostream>					// for cout etc.
//#include <vector>					// for vector class
//#include <string>					// for string class
//#include <algorithm>				// for sort algorithm
//#include <time.h>					// for random seed
//#include <math.h>					// for abs()
#include "Strings.cpp"
//#include "MiscHeader.h"

#pragma warning(disable:4786)		// disable debug warning



//#define GA_MUTATIONRATE	0.25f		// mutation rate
//#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
//#define RAND_MAX 32767

using namespace std;	
// polluting global namespace, but hey...
extern int iteratorOfRuns; 

class Queens {

public :


	int GA_POPSIZE;
	double GA_ELITRATE;
	int GA_MAXITER;
	int migrationFromEachIslands;
	int selection;
	int survivability;
	bool firstTimeToInitiatePopulation;
	bool firstTimeToRunSuS;
	long FitnessSum;
	int stepToTake;
	int indexByFitness;
	ga_vector pop_alpha, pop_beta;
	ga_vector *population, *buffer;
	int fitnessMax;
	int fitnessMin;
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


	Queens(){
		GA_POPSIZE = 2000;
		GA_ELITRATE = 0.15f;
		GA_MAXITER = 16242;
		selection = 0;
		survivability = 0;
		FitnessSum = 0;
		indexByFitness = 0;
		firstTimeToInitiatePopulation = true;
		firstTimeToRunSuS = true;
		stepToTake=0;
		fitnessMin=0;
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
						 ga_vector &buffer ) {
		for (int i=0; i<GA_POPSIZE; i++) {
			ga_struct citizen;
			citizen.age = 0;
			SetRandomBoard(citizen);
			citizen.fitness = 0;
			population.push_back((ga_struct)citizen);
		}
		buffer.resize(GA_POPSIZE);
	}


	unsigned int calculateFitnessOfBoard(ga_struct citizen, unsigned int fitness){
		fitness = 0;
		for(int col = 0 ; col < NUMBER_OF_QUEENS ; col++ ){
			for( int row = 0 ; row < NUMBER_OF_QUEENS ; row++){
				if ( abs((row - col)) == abs(citizen.board[row] - citizen.board[col])) {
						fitness++;
				}
			}
		}
		return fitness;
	}

	void calc_fitness(ga_vector &population){
		unsigned int fitness = 0;
		for(int i=0; i<GA_POPSIZE; i++) {
			fitness=calculateFitnessOfBoard(population[i], fitness);
			population[i].fitness = fitness;
		}		
	}



	static bool fitness_sort(ga_struct x, ga_struct y) 
	{ return (x.fitness < y.fitness); }

	inline void sort_by_fitness(ga_vector &population)
	{ sort(population.begin(), population.end(), fitness_sort); }

	void elitism(ga_vector &population, 
					ga_vector &buffer, int esize ){
						int counterOfAgingReplacement = 1;
		for (int i=0; i<esize; i++) {
			for ( int j =0  ; j < NUMBER_OF_QUEENS ; j++){
				buffer[i].board[j] = population[i].board[j];
			}
			buffer[i].fitness = population[i].fitness;
			buffer[i].age = population[i].age;

			if (buffer[i].age++ >= GA_MAX_AGE) {

				switch (survivability)
				{
				case 0:
					break;
				case 1:
					for ( int j =0  ; j < NUMBER_OF_QUEENS ; j++){
						buffer[i].board[j] = population[counterOfAgingReplacement + esize].board[j];
					}
					buffer[i].fitness = population[counterOfAgingReplacement + esize].fitness;
					buffer[i].age = population[esize  +(counterOfAgingReplacement++)].age;
					break;
				default:
					break;
				}

			}

		}
	}
	void swap(ga_struct &member,int position1 , int position2){
		int temp = member.board[position1];
		member.board[position1] = member.board[position2];
		member.board[position2] = temp;
		return;
	}

	/*void insert(ga_struct &member,int position1 , int position2){
		if(position1>position2){
			int temp=position2;
			position2=position1;
			position1=temp;
		}
		int temp = member.board[position1];
		for (int i = position1; i < position2; i++){
			member.board[i]=member.board[i+1];
		}
		member.board[position2]=temp;
		return;
	}*/
	void mutate(ga_struct &member)
	{
		int ipos = rand() % NUMBER_OF_QUEENS;
		int ipos2 = rand() % NUMBER_OF_QUEENS;
		while(ipos==ipos2){
			ipos2 = rand() % NUMBER_OF_QUEENS;
		}
		swap(member,ipos,ipos2);
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
			if ( ( (sum + ((fitnessMax + fitnessMin) -   (unsigned long )((*population)[i].fitness))) >= indexByFitness ) && (sum < indexByFitness)  )
				return i;
			sum += (fitnessMax + fitnessMin) -  (*population)[i].fitness;
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
			if ( ( (sum +((fitnessMax + fitnessMin)- (unsigned long )((*population)[i].fitness))) >= indexByFitness ) && (sum < indexByFitness)  )
				return i;
			sum +=(fitnessMax + fitnessMin)- (*population)[i].fitness;
		}
		return 0;
	}

	void mate(ga_vector &population, ga_vector &buffer){
		int esize = GA_POPSIZE * GA_ELITRATE;
		int i1, i2;
		elitism(population, buffer, esize);
		calculateFitnessSum();
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

			int indexToCross = rand() % NUMBER_OF_QUEENS;
			int indexToCross2 = rand() % NUMBER_OF_QUEENS;
			if( indexToCross > indexToCross2 ){
				int temp = indexToCross2;
				indexToCross2= indexToCross;
				indexToCross=temp;
			}

			TwoPointCrossover ( population[i1] , population[i2] , indexToCross  , indexToCross2 , buffer[i].board);
			fixOffspring(buffer[i].board);

			if (rand() < GA_MUTATION) mutate(buffer[i]);
		}	
	}


	void TwoPointCrossover(ga_struct &mate1,ga_struct &mate2,int pos1,int pos2, int *offspring){


		for(int i=0;i<pos1;i++){
			offspring[i]=mate1.board[i];
		}
		for(int i=pos1;i<pos2;i++){
			offspring[i]=mate2.board[i];
		}
		for(int i=pos2;i<NUMBER_OF_QUEENS;i++){
			offspring[i]=mate1.board[i];
		}
		return;
	}


	inline void print_best(ga_vector &citizen){
		string temp="";
		for (int i=0 ; i < NUMBER_OF_QUEENS ; i++){
			if(i<NUMBER_OF_QUEENS-1){
				temp += std::to_string(citizen[0].board[i]) + ",";
			}
			else{
				temp += std::to_string(citizen[0].board[i]);
			}
		}
		cout << "Best: " << temp << " (" << citizen[0].fitness << ")" <<endl;
	}

	inline void swap(ga_vector *&population,
					 ga_vector *&buffer)
	{ ga_vector *temp = population; population = buffer; buffer = temp; }


	int FindNextFreeIndexOnBoard(bool tempBoard[NUMBER_OF_QUEENS]){
			int index=0;
			while (tempBoard[index]!=false){
				index = rand() % NUMBER_OF_QUEENS;
			}
			return index;
	}

	void fixOffspring(int* offspring){
		int temp[NUMBER_OF_QUEENS]={0};
		for (int i = 0; i < NUMBER_OF_QUEENS; i++){
			temp[offspring[i]]++;
		}
		for (int i = 0; i < NUMBER_OF_QUEENS; i++){
			if(temp[offspring[i]]>1){
				int firstFreePlace = findMissingNumber(temp);
				if(firstFreePlace!=-1){
					temp[firstFreePlace] ++;
					temp[offspring[i]] --;
					offspring[i]=firstFreePlace;
				}
			}
		}
	}

	int findMissingNumber(int* tmpArray){
		for (int i = 0; i < NUMBER_OF_QUEENS; i++){
			if(tmpArray[i]==0){
				return i;
			}
		}
		return -1;
	}

	void SetRandomBoard( ga_struct &board){
		bool tempBoard[NUMBER_OF_QUEENS] = {false};
		int index =0;
		for (int i = 0;i <NUMBER_OF_QUEENS;i++){
			index= FindNextFreeIndexOnBoard(tempBoard);
			//index = rand() % NUMBER_OF_QUEENS;
			tempBoard[index] = true;
			board.board[i] = index;
		}
		return;
	}

#pragma endregion logic


	int run()
	{
		srand(unsigned(time(NULL)));
		if (firstTimeToInitiatePopulation){
			firstTimeToInitiatePopulation = false;
			init_population(pop_alpha, pop_beta);
			population = &pop_alpha;
			buffer = &pop_beta;
		}
		int i;
		for (i=0; i<GA_MAXITER; i++) {
			calc_fitness(*population);		// calculate fitness
			sort_by_fitness(*population);	// sort them
			print_best(*population);		// print the best one
						cout << "it: " << iteratorOfRuns ++ << " -- ";
			if ((*population)[0].fitness == NUMBER_OF_QUEENS) return true;

			mate(*population, *buffer);		// mate the population together
			swap(population, buffer);		// swap buffers
		}
		return 0;
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