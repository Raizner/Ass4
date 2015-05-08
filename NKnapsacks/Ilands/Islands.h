#ifndef _ISLAND_H
//#include "MiscHeader.h"
//#include "Strings.cpp"
//#include "Queens.cpp"

#include "knapsack.cpp"
#include "CeaserCypher.h"



template <class T>
class Islands{
	
#pragma region members

	T* islands;
	int numberOfIslands;
	int populationPerIsland;
	double elitismeRate;
	int epocLength;
	int migrationFromEachIsland;

#pragma endregion
	


public:

	Islands(int numberOfIslands, int populationPerIsland, double elitismeRate, int epocLength, int migrationFromEachIsland, ...) ;
	void evolve();
	void MigrationBetweenIslands();



};
#endif // !_ISLAND_H