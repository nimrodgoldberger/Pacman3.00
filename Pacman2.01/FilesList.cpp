#include"FilesList.h"
#include <filesystem>

void FilesList::getFilesFromDirectory(FileType fileType)
{
	vector<string> temp;
	std::string path = ".";
	size_t found;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		temp.push_back(string(entry.path().string()));
	}
	for (int i = 0; i < temp.size(); i++)
	{
		switch (fileType)
		{
		case FileType::screen:
			found = temp[i].find(".screen");
			if (found != string::npos)
			{
				list.push_back(temp[i]);
			}
			break;
		case FileType::steps:
			found = temp[i].find(".steps");
			if (found != string::npos)
			{
				list.push_back(temp[i]);
			}
			break;
		case FileType::results:
			found = temp[i].find(".result");
			if (found != string::npos)
			{
				list.push_back(temp[i]);
			}
			break;
			/*default:
				break;*/
		}
	}
	temp.erase(temp.begin(), temp.end());
	numOfMaps = (int)list.size();
	sortFiles();
	if (numOfMaps == 0)
	{

		cout << "No Files Found.." << endl;
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


