#ifndef STATS_H
#define STATS_H
#include <map>
#include <string>


using namespace std;

class Stats {

	int counter ;
	
public :
	Stats(string pathToEncryptedFile);
	map<string, double> occurencies;
};

#endif