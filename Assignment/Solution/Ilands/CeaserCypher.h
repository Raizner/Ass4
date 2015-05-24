#ifndef CEASERCYPHER_H
#define CEASERCYPHER_H
#include <string>
#include <fstream>


using namespace std ;

class CeaserCypher {

	string key;
	ifstream textFile;
	string originalFile;
	string outputFile;
	std::ofstream ofs;

public:
	CeaserCypher(string& key,const string& pathToFile,const string& pathToOutput);
	void createCypheredText();


	
};

#endif