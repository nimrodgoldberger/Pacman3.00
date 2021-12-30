#pragma once

#include "Game.h"
class FilesList {
private:
	int numOfMaps;
	vector<string> list;

public:
	void getFilesFromDirectory();
	void sortFiles();
	void printListOfFiles()const;
	inline vector<string> getListOfFiles()const { return list; }
	inline int getNumOfMaps()const{return numOfMaps;};
};
