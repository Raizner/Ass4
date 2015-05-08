#include "stdafx.h"
#include "Stats.h"
#include <fstream>


Stats::Stats(const string& pathToEncryptedFile, ParseText& parser){
	this->parser = &parser;
	ifstream textFile;
	string line;
	textFile.open(pathToEncryptedFile);
	while(getline(textFile, line)){

	}

}


int Stats::calculateFitness(string key){
	int fitnsess = 0;



	for(myMap::iterator i = occurencies.begin(); i != occurencies.end(); i++) {
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
		string current = (i->first);
		for (int i = 0; i < current.size(); i++)
		{
			if (current[i] >= 'a' && current[i] <= 'z')
			{

			}
			current[i] = key[current[i]];
		}

		switch (current.size())
		{
		case 1:
			if (parser->monogramFre.find(current) != parser->monogramFre.end())
			{
				if (abs( i->second - parser->monogramFre[current])  < 0.1)
				{
					fitnsess += 1;
				}
			}
			if (abs( i->second - parser->monogramFre[current])  < 0.05)
			{
				fitnsess += 5;
			}
			break;
		case 2:
			if (parser->bigramsFreIncludingSpaces.find(current) != parser->bigramsFreIncludingSpaces.end())
			{
				if (abs( i->second - parser->bigramsFreIncludingSpaces[current])  < 0.1)
				{
					fitnsess += 1;
				}
				if (abs( i->second - parser->bigramsFreIncludingSpaces[current])  < 0.05)
				{
					fitnsess += 5;
				}
			}
			break;
		case 3:
			if (parser->triagrmsFreIncludingSpaces.find(current) != parser->triagrmsFreIncludingSpaces.end())
			{
				if (abs( i->second - parser->triagrmsFreIncludingSpaces[current])  < 0.1)
				{
					fitnsess += 1;
				}
				if (abs( i->second - parser->triagrmsFreIncludingSpaces[current])  < 0.05)
				{
					fitnsess += 5;
				}
			}
			break;
		default:
			break;
		}


	}

	return fitnsess;
}