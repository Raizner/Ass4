#include "stdafx.h"
#include "parseText.h"
#include <algorithm>


ParseText
	::ParseText
	()
{
}

ParseText
	::~ParseText
	()
{
}

void ParseText::parsetMonogramFre(){

	string line;
	getline(hostRefernceFile, line); 

	while (true)
	{
		if (line.empty())
		{
			break;
		}

		string tempLetter;
		double tempFrequency;

		tempLetter = line.substr(0,1);
		tempFrequency = atof(line.substr(13,5).c_str());
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		monogramFre[tempLetter] = tempFrequency;
		//tempLetter = line.substr(24,1);
		//tempFrequency = atof(line.substr(37,4).c_str());
		//monogramFre[tempLetter] = tempFrequency;

		getline(hostRefernceFile, line); 

	}





}
void ParseText::parseBigramFrequency(map<string, double>& input){

	string line;
	getline(hostRefernceFile, line); 

	while (true)
	{
		if (line.empty())
		{
			break;
		}

		string tempLetter;
		double tempFrequency;

		tempLetter = line.substr(1,2);
		tempFrequency = stod(line.substr(14,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		tempLetter = line.substr(24,2);
		tempFrequency = stod(line.substr(37,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		tempLetter = line.substr(47,2);
		tempFrequency = stod(line.substr(60,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		getline(hostRefernceFile, line); 

	}
}

void ParseText::parseTriagrmsFrequency(map<string, double>& input){
	string line;
	getline(hostRefernceFile, line); 

	while (true)
	{
		if (line.empty())
		{
			break;
		}

		string tempLetter;
		double tempFrequency;

		tempLetter = line.substr(0,3);
		tempFrequency = stod(line.substr(14,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		tempLetter = line.substr(23,3);
		tempFrequency = stod(line.substr(37,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		tempLetter = line.substr(46,3);
		tempFrequency = stod(line.substr(60,5));
		std::transform(tempLetter.begin(), tempLetter.end(), tempLetter.begin(), ::tolower);
		input[tempLetter] = tempFrequency;
		getline(hostRefernceFile, line); 

	}
}



void ParseText::createStatistics(const string& fileName){

	ifstream hostRefernceFile;
	hostRefernceFile.open(fileName);
	string line;
	int counter =0;
	while (getline(hostRefernceFile, line)){
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		for(int i=0;i<line.length();i++){
			char temp1 = line[i];
			if ((temp1 >= 'a' && temp1 <=  'z') || temp1 == ' ')
			{
				lettersStatistics[line.substr(i,1)]+=1;
				counter++;
			}
			
		}
	}
	for(map<string,double>::iterator iterator = lettersStatistics.begin(); iterator != lettersStatistics.end(); iterator++) {
		iterator->second=(iterator->second/(double)counter)*100;
	}


	hostRefernceFile.close();
	return;
}

void ParseText::parseTextLunch(const string& fileName){


	hostRefernceFile.open(fileName);
	string line;
	char* nextToken = "";
	//int m_lineIndex = 0;

	while (getline(hostRefernceFile, line))
	{
		if (line.find("Word lengths") != string::npos)
		{
			parsetLettersOcc();

		}
		if (line.find("Monogram frequencies")!= string::npos)
		{
			parsetMonogramFre();

		}
		if (line.find("Most common bigrams including space") != string::npos)
		{
			parseBigramFrequency(bigramsFreIncludingSpaces);

		}
		if (line.find("Most common bigrams in the beginning of words") != string::npos)
		{
			parseBigramFrequency(bigramsFreBeginningOfWords);

		}
		if (line.find("Most common bigrams in the end of words") != string::npos)
		{
			parseBigramFrequency(bigramsFreEndEfWords);

		}
		if (line.find("Most common bigrams not including space") != string::npos)
		{
			parseBigramFrequency(bigramsFreNoSpaces);

		}
		if (line.find("Most common trigrams including space") != string::npos)
		{
			parseTriagrmsFrequency(triagrmsFreIncludingSpaces);
		}
		if (line.find("Most common trigrams not including space") != string::npos)
		{
			parseTriagrmsFrequency(triagrmsFreIncludingNoSpaces);
		}

	}

	hostRefernceFile.close();

}

int ParseText::calculateGCD(){

	ifstream toGCDINT;
	hostRefernceFile.open("c:\\temp\\text\\vigener.txt");
	string line;
	int numberOfLine = 0;
	while (getline(hostRefernceFile, line)){
		for (int i = 0; i < line.size() - 3; i++)
		{
			string goToMap = line.substr(i, 3);
			gcdKassiski[goToMap].push_back(numberOfLine+i);
		}
		numberOfLine += line.size();
	}
	
	map<string, list<int>>::iterator biggestSubString = gcdKassiski.begin();
	for (map<string, list<int>>::iterator it ; it != gcdKassiski.end() ; it++)
	{
		if (it->second.size() > biggestSubString->second.size())
		{
			biggestSubString = it;
		}
	}

	return getGCDFromList(biggestSubString->second);
}

void ParseText::parsetLettersOcc(){

	string line;
	getline(hostRefernceFile, line); 

	while (true)
	{
		if (line.empty())
		{
			break;
		}

		int tempLetter;
		double tempFrequency;

		tempLetter = atoi(line.substr(1,2).c_str());
		tempFrequency = atof(line.substr(14,4).c_str());
		lettersOcc[tempLetter] = tempFrequency;
		getline(hostRefernceFile, line); 

	}

}