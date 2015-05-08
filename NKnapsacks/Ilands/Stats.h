#ifndef STATS_H
#define STATS_H
#include <map>
#include <string>


using namespace std;

class Stats {

	
	
public :
	Stats(string pathToEncryptedFile);
	map<string, int> occurencies;
};

#endif