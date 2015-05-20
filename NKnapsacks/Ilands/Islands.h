#ifndef _ISLAND_H
#define _ISLAND_H
//#include "MiscHeader.h"
//#include "Strings.cpp"
//#include "Queens.cpp"


#include "knapsack.cpp"
#include "CeaserCypher.h"
#include "Crypt.cpp"
#include <string>

template <class T>
class Islands{

	public:
#pragma region members

	T* islands;
	int numberOfIslands;
	int populationPerIsland;
	double elitismeRate;
	int epocLength;
	int migrationFromEachIsland;

#pragma endregion
	




	Islands(int numberOfIslands, int populationPerIsland, double elitismeRate, int epocLength, int migrationFromEachIsland, ...) ;
	int evolve();
	void MigrationBetweenIslands();



};
#endif // !_ISLAND_H