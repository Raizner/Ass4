#include "stdafx.h"
#include "Stats.h"
#include <fstream>


Stats::Stats(const string& pathToEncryptedFile, ParseText& parser){
	this->parser = &parser;
	this->counter=0;
	ifstream textFile;
	string line;
	textFile.open(pathToEncryptedFile);
	while(getline(textFile, line)){
		for(int i=0;i<line.length();i++){
			string oneLetter = line.substr(i,1);
			char tempChar = oneLetter.c_str()[0];
			if(tempChar >='a' && tempChar <='z'){
				occurencies[oneLetter]=occurencies[oneLetter]+1;
			}
			string twoLetters ;
			string threeLetters;
			if(!(i>line.length()-1)){
				char temp1 = ((line.substr(i+1,1)).c_str())[0];
				if ((temp1 >= 'a' && temp1 <=  'z') || temp1 == ' '){
					twoLetters= line.substr(i,2);
					occurencies[twoLetters] = occurencies[twoLetters]+1;
				}
			}
			if(!(i>line.length()-2)){
				char temp2 = ((line.substr(i+1,1)).c_str())[0];
				char temp3 = ((line.substr(i+2,1)).c_str())[0];
				if((temp2 >= 'a' && temp2 <=  'z') && (temp3 >= 'a' && temp3 <=  'z')){
					threeLetters = line.substr(i,3);
					occurencies[threeLetters]=occurencies[threeLetters]+1;
				}
				
			}
			//occurencies[twoLetters] = occurencies[twoLetters]+1;
			counter++;
		}

	}
	for(map<string,double>::iterator iterator = occurencies.begin(); iterator != occurencies.end(); iterator++) {
		if(iterator->first.length()==1){
			iterator->second=(iterator->second/(double)counter)*100;
		}
		if(iterator->first.length()==2){
			iterator->second=(iterator->second/(double)(counter-1))*100;
		}
		if(iterator->first.length()==3){
			iterator->second=(iterator->second/(double)(counter-2))*100;
		}
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