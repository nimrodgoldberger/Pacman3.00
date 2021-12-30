#include"FilesList.h"
#include <filesystem>

void FilesList::getFilesFromDirectory()
{
	vector<string> temp;
	std::string path = ".";

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		temp.push_back(string(entry.path().string()));
	}
	for (int i = 0; i < temp.size(); i++)
	{
		size_t found = temp[i].find(".screen");
		if (found != string::npos)
		{
			list.push_back(temp[i]);
		}
	}
	temp.erase(temp.begin(), temp.end());
	numOfMaps = (int)list.size();
	sortFiles();
	if (numOfMaps == 0) 
	{

		cout << "No Files Found.."<<endl;
	}
		
}
void FilesList::sortFiles()
{
	std::sort(list.begin(), list.end());
}
void FilesList::printListOfFiles()const
{
	for (string s : list)
	{
		cout << s << endl;
	}
}


