#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>


#include <map>
#include <list>

using namespace std;
class ParseText

{
public:

	ifstream hostRefernceFile;
	map<int, double> lettersOcc;
	map<string,double> lettersStatistics;
	map<string, double> monogramFre;
	
	map<string, double> bigramsFreIncludingSpaces;
	map<string, double> bigramsFreBeginningOfWords;
	map<string, double> bigramsFreEndEfWords;
	map<string, double> bigramsFreNoSpaces;

	map<string, double> triagrmsFreIncludingSpaces;
	map<string, double> triagrmsFreIncludingNoSpaces;

	map<string, list<int>> gcdKassiski;
	
	ParseText
();
	~ParseText
();
	void parseTextLunch(const string& filename);
	void parsetLettersOcc();
	void parsetMonogramFre();
	void parseBigramFrequency(map<string, double>&);
	int getGCDFromList(list<int> listOfInt);
	void parseTriagrmsFrequency(map<string, double>&);
	void createStatistics(const string& fileName);

	int calculateGCD();

private:

};





 #endif