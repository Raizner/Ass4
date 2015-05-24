// Ilands.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Islands.h"
#include <stdarg.h>
#include "parseText.h"
#include "Stats.h"



namespace {

	void devideToFIlesByGCD(int numberOfFiles){

		string* filesString = new string[numberOfFiles];
		for (int i = 0; i < numberOfFiles; i++)
		{
			filesString[i] = "";
		}
		size_t iNUmber = 0;
		ifstream toGCDINT;
		toGCDINT.open("text\\vigener.txt");
		string line;
		int numberOfLine = 0;
		while (getline(toGCDINT, line)){
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] != ' ')
				{					
					filesString[iNUmber % numberOfFiles] += line[i];

					++iNUmber;

				}

			}

		}

		for (int i = 0; i < numberOfFiles; i++)
		{
			string filename = "text\\" + to_string(i) + ".txt";
			ofstream writeToFile(filename);
			writeToFile << filesString[i];
			writeToFile.close();
		}



	}
}

int iteratorOfRuns=0;

template <class T>
int Islands<T>::evolve(){

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

	try {
		return static_cast<int>((*islands->population)[0].fitness);
	}
	catch (...) {
		return 0;
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


	//ParseText parser;

	//parser.parseTextLunch("text\\freq.txt");
	//string temp = "nyrfcetpxsuawdgikhqjzombvl";
	//CeaserCypher cc(temp, "text\\input.txt", "text\\encryptedText.txt");
	//cc.createCypheredText();



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
	


	ParseText parser;

	parser.parseTextLunch("text\\freq.txt");

	Stats stat("text\\input.txt", parser);
	string temp = "nyrfcetpxsuawdgikhqjzombvl";
	CeaserCypher cc(temp, "text\\input.txt", "text\\encryptedText.txt");
	cc.createCypheredText();

	cout << "The encrypted text located in current directory + text\\encryptedText.txt" << endl;

	getchar();

	return 0;


#if 0

	ParseText parser;
	//Kasiski method implementation
	vector<int> bestPractice;
	for(int j=2;j<20;j++){
		devideToFIlesByGCD(j);

		for(int i=0;i< j ; i++ ){
			Islands<Crypt> newIslands(1, 1200, 0.1f, 50, 0 , 0 , 0);

			newIslands.islands->setStats("text\\"+to_string(i)+".txt");

			bestPractice.push_back(newIslands.evolve());
		}

	}

	int IC = bestPractice[0];

	Islands<Crypt> newIslands(1, 1200, 0.1f, 50, 0 , 0 , 0);

	newIslands.islands->setStats("text\\"+to_string(IC)+".txt");
	newIslands.evolve();


	/*int GCD = parser.calculateGCD();



	devideToFIlesByGCD(GCD);
	cout << "VERY FAST GCD: " << GCD << endl;*/
	//Islands<Crypt> newIslands(1, 1200, 0.1f, 50, 0 , 0 , 0);
	//


	//newIslands.evolve();
	//for(int i=0;i< GCD ; i++ ){
	//	Islands<Crypt> newIslands(1, 1200, 0.1f, 50, 0 , 0 , 0);

	//	newIslands.islands->setStats("text\\"+to_string(i)+".txt");

	//	newIslands.evolve();
	//}
	//return 0;

#endif
}

