#ifndef STATS_H
#define STATS_H
#include <map>
#include <string>
#include "parseText.h"

typedef std::map<std::string, double> myMap;

using namespace std;

class Stats {

	ParseText* parser;
	
public :
	Stats(const string& pathToEncryptedFile, ParseText& parser);
	map<string, double> occurencies;

	int calculateFitness(string key);
};

#endif