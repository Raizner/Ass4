// Ilands.cpp : Defines the entry point for the console application.
//
#include "Crypt.cpp"
#include "stdafx.h"
#include "Islands.h"
#include <stdarg.h>
#include "parseText.h"


int iteratorOfRuns=0;

template <class T>
void Islands<T>::evolve(){

	while(true){

		bool finishRun = false;
		for (int i = 0; i < numberOfIslands; i++)
		{
			cout << "Running island number: " << i << endl;
			if (islands[i].run()){
				finishRun = true;
				break;
			}
		}
		if (finishRun) {
			break;
		}
		if (numberOfIslands > 1) {
			MigrationBetweenIslands();
		}
	}

}

template <class T>
void Islands<T>::MigrationBetweenIslands(){

	int i = 0;
	int numberOfChosenIland = (i-1 + numberOfIslands) % numberOfIslands;
	ga_vector *citzens1 = islands[numberOfChosenIland].getForReplacment();
	ga_vector *citzens2 = citzens1;
	for (; i < numberOfIslands; i++)
	{
		if (i != numberOfIslands -1 ) {
			citzens2 = islands[(i) % numberOfIslands].getForReplacment();
		}
		islands[i].SetForReplacment( *citzens1);
		citzens1 = citzens2;
	}

}

template <class T>
Islands<T>::Islands(int numberOfIslands, int populationPerIsland, double elitismeRate, int epocLength, int migrationFromEachIsland, ...) {

	this->numberOfIslands = numberOfIslands;
	this->populationPerIsland = populationPerIsland;
	this->elitismeRate = elitismeRate;
	this->epocLength = epocLength;
	this->migrationFromEachIsland = migrationFromEachIsland;

	islands = new T[numberOfIslands];

	int numberOfSUp = numberOfIslands * 2;
	va_list ap;
	va_start(ap,migrationFromEachIsland );

	for (int i = 0; i < numberOfIslands; i++)
	{
		int tempVar1 = va_arg(ap, int);
		int tempVar2 = va_arg(ap, int);
		if (numberOfIslands == 1)
		{
			islands[i].initialize(tempVar1, tempVar2, populationPerIsland, elitismeRate, 16300, migrationFromEachIsland);
		} else {
			islands[i].initialize(tempVar1, tempVar2, populationPerIsland, elitismeRate, epocLength, migrationFromEachIsland);
		}
	}

	va_end(ap);
}


int _tmain(int argc, _TCHAR* argv[])
{


	ParseText parser;

	parser.parseTextLunch("C:\\temp\\freq.txt");
	string temp = "nyrfcetpxsuawdgikhqjzombvl";
	CeaserCypher cc(temp, "c:\\temp\\text\\input.txt", "c:\\temp\\text\\output.txt");
	cc.createCypheredText();

	return 0;

	/*

	selection:	
	0 - default
	1 - RWS
	2 - SUS

	survivability:
	0 - No aging default
	1 - Default aging ( "taking" the next in line)
	2 - GENITOR

	*/
	Islands<knapsack> newIslands(3, 2000, 0.1f, 50, 0,0,1,1,1,2,1);

	newIslands.evolve();

	return 0;
}

