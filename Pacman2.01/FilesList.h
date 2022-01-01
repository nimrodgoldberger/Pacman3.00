#pragma once

#include "Game.h"
enum class FileType { screen, steps, results };


class FilesList {
private:
	int numOfMaps;
	vector<string> list;

public:
	void getFilesFromDirectory(FileType fileType);
	void sortFiles();
	void printListOfFiles()const;
	inline vector<string> getListOfFiles()const { return list; }
	inline int getNumOfMaps()const{return numOfMaps;};
};
