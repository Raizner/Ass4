#include "stdafx.h"
#include "CeaserCypher.h"


CeaserCypher::CeaserCypher(string& key,const string& pathToFile,const string& pathToOutput){
	this->key = key;
	this->originalFile=pathToFile;
	this->outputFile=pathToOutput;

	ofs.open(outputFile, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void CeaserCypher::createCypheredText(){
	textFile.open(originalFile);
	ofs.open(outputFile);
	string line;
	string encryptedLine;
	while(getline(textFile, line)){
		encryptedLine = line;
		for (int i = 0; i < line.length(); i++)
		{
			char temp = line[i];
			if(temp <= 'Z' && temp >='A')
			{
				temp =  temp - ('Z'-'z');
			}
			if ((temp >= 'a' && temp <=  'z'))
			{
				
				encryptedLine[i] = key.find(temp) + 'a';
			}
		}
		this->ofs << encryptedLine << endl;
	}
	textFile.close();
	ofs.close();
}


