// Genetic5.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Queens.cpp"


//#define GA_MUTATIONRATE	0.25f		// mutation rate
//#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
//#define GA_TARGET		std::string("01000100011110000011111")
//#define GA_MAX_BAG_WEIGHT 1000
//#define NUMBER_OF_OBJECTS 20

/*
# Optimal? selection:
# ITEM	ITEMWEIGHT	ITEMVALUE
# 5		539	996
# 11	54	941
# 13	18	974
# 16	169	507
# 17	36	711
#		816	4129
*/

using namespace std;				// polluting global namespace, but hey...

extern int iteratorOfRuns; 

/*static int itemsKnapsack[2][NUMBER_OF_OBJECTS] = {{540 , 60 , 53, 756 , 996,424,564,776,922,438,941,116,974,214,122,507,711,838,338,887},{873 , 713 , 928 , 360 , 539,446,681,756,629,757,54,670,18,530,358,169,36,713,601,931}};
static int itemsKnapsack[NUMBER_OF_SACKS+1][NUMBER_OF_OBJECTS] = {{560 ,1125,68,328,47,122,196,41, 25	,115, 82, 22  , 631  , 132  , 420	, 86   , 42  , 103  ,  81	, 26, 49,	316 ,   72   , 71,    49	,108  , 116  ,  90  },
{   40, 91,	3  ,  12  ,   3	, 18 ,   25  ,   1  ,   1	 , 8, 1	,  1  ,  49  ,   8   , 21	,  6	,1 ,    5   ,  8	,  1,  0	, 42	,6   ,  4  ,   8,	  0   , 10  ,   1 } ,
{   16, 92,4 , 18,  6, 0,8,  2 , 1	,6,2, 1,70 ,9, 22,4,1, 5 , 6,0,4, 8,4, 3,0,10,0,6 },
{   38, 39, 5, 40,  8, 12, 15,  0, 1, 20, 3, 0 , 40,  6, 8, 0	, 6 , 4, 4,  1,  5, 8, 2, 8,  0, 20, 0,  0 },
{   38,52,7 ,20, 0,3,4,1,2,4,6,1,18 ,15, 38,10,4,8,0,3,0, 6,1,3,0,3,5,4 }};

static int knapSacksCapactities[NUMBER_OF_SACKS]={219,203,208,180};
*/
//Number of sacks here is 2 and objects is 28
/*
static int itemsKnapsack[NUMBER_OF_SACKS+1][NUMBER_OF_OBJECTS]={{1898  ,  440  ,22507  ,   270 , 14148  , 3100   ,4650  ,30800 ,   615 ,  4975,
																1160  , 4225 ,   510   ,11880  ,  479 ,   440   , 490  ,  330  ,  110  ,  560,
																24355  , 2885 , 11748   , 4550  ,  750  , 3720  , 1950 , 10500 },
{45   ,   0    , 85 ,    150    , 65     ,95 ,    30  ,    0,   170 ,     0,
     40  ,   25 ,    20 ,     0   ,   0 ,    25   ,   0  ,    0  ,   25 ,     0,
    165  ,    0   ,  85    ,   0    ,  0  ,    0,      0  ,  100  },
{
	     30 ,    20   , 125   ,    5  ,   80    , 25  ,   35  ,   73 ,   12  ,   15,
     15   ,  40   ,   5  ,    10    , 10    , 12   ,  10 ,     9   ,   0  ,   20,
     60   ,  40  ,   50  ,    36,     49   ,  40  ,   19   , 150 
}};
static int knapSacksCapactities[NUMBER_OF_SACKS]={600,600};
*/
//141278  optimum value



//Number of sacks here is 4 and objects is 35
static int itemsKnapsack[NUMBER_OF_SACKS+1][NUMBER_OF_OBJECTS]={{  560,  1125  , 620   , 68 ,  328,	 47  , 122 ,  196 ,   41,	 25,
  115,	 82  ,  22 ,  631 ,  132,	420   , 86  ,  42,   103	,215,
   81	, 91  ,  26  ,  49 ,  316,	 72  ,  71 ,   49   ,108	,116,
   90,	215  ,  58   , 47 ,   81,	 },
{  40	, 91 ,   30  ,   3  ,  12	 , 3,    18   , 25 ,    1	,  1,
    8	,  1,	1   , 49 ,    8	, 21,	6  ,   1  ,   5	 ,10,
    8,	  2	,1 ,    0  ,  42,	  6	,4 ,    8,     0	, 10,
    1	,  8,	3 ,    2,     4	 },
{
	    16	, 92   , 16 ,    4 ,  18,	  6	,0   ,  8 ,    2	,  1,
    6	,  2,	1 ,   70   , 9	 ,22,	4  ,   1 ,    5	 ,10,
    6	,  4,	0  ,   4,     8,	  4,	3 ,    0  ,  10	,  0,
    6	, 22,	0   ,  2 ,    2	
},
{
   38	, 39  ,  71 ,    5 ,   40	,  8   , 12 ,   15    , 0	 , 1,
   20	,  3,	0    ,40    , 6	,  8	,0  ,   6 ,    4	, 22,
    4	,  6	,1,     5  ,   8	,  2,	8  ,   0 ,   20,	  0,
    0	, 13	,6 ,    1    , 2	
},
{
  38	 ,52    ,42   ,  7  ,  20	,  0,	3   ,  4   ,  1	 , 2,
    4,	  6,	1  ,  18  ,  15	, 38  ,  10 ,    4   ,  8	,  6,
    0	,  0,	3   ,  0  ,   6	 , 1	,3  ,   0   ,  3	,  5,
    4	, 18,	3   ,  4   ,  0	
}
};// Optima 3186
static int knapSacksCapactities[NUMBER_OF_SACKS]={  163,	165 ,  239  , 168 	};





class knapsack {


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


	knapsack() {



		GA_POPSIZE = 2000;
		GA_ELITRATE = 0.15f;
		GA_MAXITER = 16242;
		selection = 0;
		survivability = 0;
		FitnessSum = 0;
		indexByFitness = 0;
		firstTimeToInitiatePopulation = true;
		firstTimeToRunSuS = true;


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


	void init_population(ga_vector &population,
		ga_vector &buffer ) 
	{
		int tsize = GA_TARGET.size();

		for (int i=0; i<=GA_POPSIZE; i++) {
			ga_struct citizen;
			citizen.fitness = 0;
			citizen.str.erase();
			for (int j=0; j<MAX_NUMBER_OF_ITEMS; j++){
				citizen.bag[j] = (rand() % 2);
			}
			for(int k=0;k<NUMBER_OF_SACKS;k++){
				citizen.weight[k]=0;
				citizen.knapsackFitness[k] = 0;
			}
			population.push_back(citizen);
		}

		buffer.resize(GA_POPSIZE);
	}


	void calc_fitness(ga_vector &population)
	{
		string target = GA_TARGET;
		int tsize = target.size();
		for (int i=0; i<GA_POPSIZE; i++) {
			int counter=0;
			int fitness[NUMBER_OF_SACKS]={0};
			population[i].fitness = 0;
			for(int k=0;k<NUMBER_OF_SACKS;k++){
				population[i].weight[k] = 0;
				population[i].knapsackFitness[k] = 0;
				for (int j=0; j<MAX_NUMBER_OF_ITEMS; j++) {
					if(population[i].bag[j]==1 ){
						population[i].weight[k] += itemsKnapsack[k+1][j];
						//weight[k]+=itemsKnapsack[k+1][j];
						population[i].knapsackFitness[k]+=itemsKnapsack[0][j];//value stays the same , weight changes
					}
					if(population[i].weight[k]>knapSacksCapactities[k]){
						counter++;
					}
				}
			}
			for(int l=0;l<NUMBER_OF_SACKS;l++){
				if(population[i].weight[l]>knapSacksCapactities[l]){
					population[i].knapsackFitness[l]=NUMBER_OF_OBJECTS/counter;
				}
			}
			if(counter==0){
				population[i].fitness = population[i].knapsackFitness[0];
				for(int m=1;m<NUMBER_OF_SACKS;m++){
					if(population[i].fitness < population[i].knapsackFitness[m]){
						population[i].fitness = population[i].knapsackFitness[m];
					}
				}
			}
			else {
				population[i].fitness=20/counter;

			}
		}
	}

	static bool fitness_sort(ga_struct x, ga_struct y) 
	{ return (x.fitness > y.fitness); }

	inline void sort_by_fitness(ga_vector &population)
	{ sort(population.begin(), population.end(), fitness_sort); }

	void elitism(ga_vector &population, 
		ga_vector &buffer, int esize )
	{
		int counterOfAgingReplacement = 1;
		for (int i=0; i<esize; i++) {
			buffer[i].str = population[i].str;
			buffer[i].fitness = population[i].fitness;
			buffer[i].age = population[i].age;
			for(int l=0;l<NUMBER_OF_SACKS;l++){
				buffer[i].weight[l]=population[i].weight[l];
				for ( int j =0  ; j < MAX_NUMBER_OF_ITEMS ; j++){
					buffer[i].bag[j] = population[i].bag[j];
				}
			}

			if (buffer[i].age++ >= GA_MAX_AGE) {
				switch (survivability)
				{
				case 0:
					break;
				case 1:
					for(int l=0;l<NUMBER_OF_SACKS;l++){
						buffer[i].weight[l]=population[esize +i].weight[l];
						for ( int j =0  ; j < MAX_NUMBER_OF_ITEMS ; j++){
							buffer[i].bag[j] = population[counterOfAgingReplacement+esize].bag[j];
						}
					}
					buffer[i].fitness = population[counterOfAgingReplacement + esize].fitness;
					buffer[i].age = population[esize +(counterOfAgingReplacement++)].age;
					break;
				default:
					break;
				}
			}
		}
	}	
	void swap(ga_struct &member,int position1 , int position2){
		int temp = member.bag[position1];
		member.bag[position1] = member.bag[position2];
		member.bag[position2] = temp;
		return;
	}

	void mutate(ga_struct &member)
	{
		int ipos = rand() % MAX_NUMBER_OF_ITEMS;
		int ipos2 = rand() % MAX_NUMBER_OF_ITEMS;
		while(ipos==ipos2){
			ipos2 = rand() % MAX_NUMBER_OF_ITEMS;
		}
		swap(member,ipos,ipos2);
	}

	void calculateFitnessSum(){
		int RWSSum = 0;
		for (int j = 0; j < population->size();  j++)
		{

			RWSSum += (*population)[j].fitness;
		}

		this->FitnessSum = RWSSum;
	}

	void mate(ga_vector &population, ga_vector &buffer)
	{
		int esize = GA_POPSIZE * GA_ELITRATE;
		int tsize = GA_TARGET.size(), spos, i1, i2;

		calculateFitnessSum();

		elitism(population, buffer, esize);

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

			int indexToCross = rand() % MAX_NUMBER_OF_ITEMS;
			int indexToCross2 = rand() % MAX_NUMBER_OF_ITEMS;
			if( indexToCross > indexToCross2 ){
				int temp = indexToCross2;
				indexToCross2= indexToCross;
				indexToCross=temp;
			}
			TwoPointCrossover ( population[i1] , population[i2] , indexToCross  , indexToCross2 , buffer[i].bag);
			for(int l=0;l<NUMBER_OF_SACKS;l++){
				buffer[i].weight[l] = 0 ;
				buffer[i].knapsackFitness[l] = 0;
			}
			if (rand() < GA_MUTATION) mutate(buffer[i]);
			buffer[i].fitness = 0;
		}
	}

	void TwoPointCrossover(ga_struct &mate1,ga_struct &mate2,int pos1,int pos2, int *offspring){
		for(int i=0;i<pos1;i++){
			offspring[i]=mate1.bag[i];
		}
		for(int i=pos1;i<pos2;i++){
			offspring[i]=mate2.bag[i];
		}
		for(int i=pos2;i<MAX_NUMBER_OF_ITEMS;i++){
			offspring[i]=mate1.bag[i];
		}


		return;
	}



	inline void print_best(ga_vector &gav)
	{ 
		cout << "Best value: "  << gav[0].fitness << endl;
		for(int i=0;i<NUMBER_OF_SACKS;i++){
			cout << "Weight of the bag : " << gav[0].weight[i] << endl;
			printTheItems(gav,i);
		}

	}

	void printTheItems(ga_vector &gav,int bagNumber){
		cout<< " We took items number : " ;
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			if(gav[0].bag[i]==1){
				cout << i << ",";
			}
		}
		cout << endl;
	}

	inline void swap(ga_vector *&population,
		ga_vector *&buffer)
	{ ga_vector *temp = population; population = buffer; buffer = temp; }


	int getIndexByRWS( )
	{
		long sum = 0;
		indexByFitness = rand() % (FitnessSum);
		for (int i = 0 ; i < population->size() ; i++)
		{
			if ( ( (sum + (unsigned long )((*population)[i].fitness)) >= indexByFitness ) && (sum < indexByFitness)  )
				return i;
			sum += (*population)[i].fitness;
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
			if ( ( (sum + (unsigned long )((*population)[i].fitness)) >= indexByFitness ) && (sum < indexByFitness)  )
				return i;
			sum += (*population)[i].fitness;
		}
		return 0;

	}


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
			if ((*population)[0].fitness == 0) {
				return true;
				break;
			}
			mate(*population, *buffer);		// mate the population together
			swap(population, buffer);		// swap buffers
		}

		return false;
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


};