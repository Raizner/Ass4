#include "stdafx.h"
#include "Stats.h"
#include <fstream>


Stats::Stats(string pathToEncryptedFile){
	ifstream textFile;
	string line;
	textFile.open(pathToEncryptedFile);
	while(getline(textFile, line)){

	}

}