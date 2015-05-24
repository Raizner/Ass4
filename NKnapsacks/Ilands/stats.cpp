#include "stdafx.h"
#include "Stats.h"
#include <fstream>


Stats::Stats(const string& pathToEncryptedFile, ParseText& parser){
	this->parser = &parser;
	this->parser->parseTextLunch("text\\freq.txt");
	this->parser->createStatistics("text\\inputToStatistcs.txt"); // the parsing of the real text - artyom BOM!!!
	this->counter=0;
	ifstream textFile;
	string line;
	textFile.open(pathToEncryptedFile);
	while(getline(textFile, line)){
		for(int i=0;i<line.length();i++){

			string oneLetter = line.substr(i,1);
			char tempChar = oneLetter.c_str()[0];
			if((tempChar >='a' && tempChar <='z') || tempChar == ' ' ){
				occurencies[oneLetter]=occurencies[oneLetter]+1;
				counter++;
			}


			//string twoLetters ;
			//
			//if(!(i>line.length()-1)){
			//	char temp1 = ((line.substr(i,1)).c_str())[0];
			//	char temp2 = ((line.substr(i+1,1)).c_str())[0];
			//	if (( (temp1 >= 'a' && temp1 <=  'z') || temp1 == ' ' ) &&  ((temp2 >= 'a' && temp2 <=  'z') || temp2 == ' ' )){
			//		twoLetters= line.substr(i,2);
			//		if ((parser.bigramsFreIncludingSpaces.find(twoLetters) != parser.bigramsFreIncludingSpaces.end()))
			//		{
			//			occurencies[twoLetters] = occurencies[twoLetters]+1;
			//		}
			//	}
			//}



			//string threeLetters;
			//if(!(i>line.length()-2)){
			//	char temp1 = ((line.substr(i,1)).c_str())[0];
			//	char temp2 = ((line.substr(i+1,1)).c_str())[0];
			//	char temp3 = ((line.substr(i+2,1)).c_str())[0];
			//	if (( (temp1 >= 'a' && temp1 <=  'z') || temp1 == ' ' ) &&  ((temp2 >= 'a' && temp2 <=  'z') || temp2 == ' ' )
			//			&& ((temp3 >= 'a' && temp3 <=  'z') || temp3 == ' ' )){
			//		threeLetters = line.substr(i,3);
			//		if ((parser.triagrmsFreIncludingSpaces.find(threeLetters) != parser.triagrmsFreIncludingSpaces.end())){
			//		occurencies[threeLetters]=occurencies[threeLetters]+1;
			//		}
			//	}

			//}
			//occurencies[twoLetters] = occurencies[twoLetters]+1;
			
		}

	}
	for(map<string,double>::iterator iterator = occurencies.begin(); iterator != occurencies.end(); iterator++) {
		if(iterator->first.length()==1){
			iterator->second=(iterator->second/(double)counter)*100;
		}
		//if(iterator->first.length()==2){
		//	iterator->second=(iterator->second/(double)(counter-1))*100;
		//}
		//if(iterator->first.length()==3){
		//	iterator->second=(iterator->second/(double)(counter-2))*100;
		/*}*/
	}

}


int Stats::calculateFitness(string key){
	int fitnsess = 0;



	for(myMap::iterator i = occurencies.begin(); i != occurencies.end(); i++) {
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
		string currentEnctypetdLetters = (i->first);
		for (int i = 0; i < currentEnctypetdLetters.size(); i++)
		{
			if ( (currentEnctypetdLetters[i] >= 'a') && (currentEnctypetdLetters[i] <= 'z'))
			{
				currentEnctypetdLetters[i] = key[currentEnctypetdLetters[i] - 'a'];
			}

		}

		switch (currentEnctypetdLetters.size())
		{
		case 1:
			if (parser->lettersStatistics.find(currentEnctypetdLetters) != parser->lettersStatistics.end())
			{
				if (abs( i->second - parser->lettersStatistics[currentEnctypetdLetters])  < 0.5)
				{
					fitnsess += 1;
				}

				if (abs( i->second - parser->lettersStatistics[currentEnctypetdLetters])  < 0.2)
				{
					fitnsess += 5;
				}
			}
			break;
		//case 2:
		//	if (parser->bigramsFreIncludingSpaces.find(currentEnctypetdLetters) != parser->bigramsFreIncludingSpaces.end())
		//	{
		//		if (abs( i->second - parser->bigramsFreIncludingSpaces[currentEnctypetdLetters])  < 1)
		//		{
		//			fitnsess += 1;
		//		}
		//		if (abs( i->second - parser->bigramsFreIncludingSpaces[currentEnctypetdLetters])  < 0.5)
		//		{
		//			fitnsess += 2;
		//		}
		//	}
		//	break;
		//case 3:
		//	if (parser->triagrmsFreIncludingSpaces.find(currentEnctypetdLetters) != parser->triagrmsFreIncludingSpaces.end())
		//	{
		//		if (abs( i->second - parser->triagrmsFreIncludingSpaces[currentEnctypetdLetters])  < 1)
		//		{
		//			fitnsess += 1;
		//		}
		//		if (abs( i->second - parser->triagrmsFreIncludingSpaces[currentEnctypetdLetters])  < 0.5)
		//		{
		//			fitnsess += 2;
		//		}
		//	}
			break;
		default:
			break;
		}


	}

	return fitnsess;
}