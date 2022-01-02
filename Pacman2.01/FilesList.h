#pragma once

#include "Game.h"
enum class FileType { screen, steps, results };
class InputParser {
public:
	InputParser(int& argc, char** argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	
	bool cmdOptionExists(const std::string& option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}
private:
	std::vector <std::string> tokens;
};

class FilesList {
private:
	int numOfMaps;
	vector<string> list;

public:
	void getFilesFromDirectory(FileType fileType);
	void sortFiles();
	void printListOfFiles()const;
	inline void setListOfFiles(vector<string> newList) { list = newList; numOfMaps = newList.size(); }
	inline vector<string> getListOfFiles()const { return list; }
	inline int getNumOfMaps()const{return numOfMaps;};
	inline void decreaseNumOfMaps() { numOfMaps--; }
	void makeSureFilesAreThere(FilesList& stepOrResult, FileType fileType, InputParser input);
};
