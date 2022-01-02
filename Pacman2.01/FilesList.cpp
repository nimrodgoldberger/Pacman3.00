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
	if (numOfMaps == 0 &&fileType==FileType::screen)
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

void FilesList::makeSureFilesAreThere(FilesList& stepOrResult, FileType fileType ,InputParser input)
{
	stepOrResult.getFilesFromDirectory(fileType);
	if (input.cmdOptionExists("-load"))
	{
		if (stepOrResult.getNumOfMaps()==0)
		{
			//no matching files ERROR and close
			cout << "ERROR!! No files to load!!" << endl;
			exit(1);
		}
		else if (numOfMaps < stepOrResult.getNumOfMaps())
		{
			int k = 0;
			int j = 0;
			string temp;
			for (int i = 0; i < stepOrResult.getNumOfMaps(); i++)
			{
				temp.clear();
				temp = stepOrResult.getListOfFiles()[i];
				while (temp[k] != '.')
				{
					k++;
				}
				/*newList.push_back(temp.substr(0, k + 1));*///review this part
				if (list[j] == temp.substr(0, k + 1) + ".screen")
				{
					j++;//exists
				}
				else
				{
					stepOrResult.getListOfFiles().erase(stepOrResult.getListOfFiles().begin() + i);
					stepOrResult.decreaseNumOfMaps();
					i--;
				}
				k = 0;
			}
			if (stepOrResult.getNumOfMaps() == 0)
			{
				//no matching files ERROR and close
				cout << "ERROR!! No Matching files to load!!" << endl;
				exit(1);
			}
		}
		else if (numOfMaps > stepOrResult.getNumOfMaps())
		{
			//int k = 0;
			//int j = 0;
			//string temp;
			//for (int i = 0; i < stepOrResult.getNumOfMaps(); i++)
			//{
			//	temp.clear();
			//	temp = stepOrResult.getListOfFiles()[i];
			//	while (temp[k] != '.')
			//	{
			//		k++;
			//	}
			//	/*newList.push_back(temp.substr(0, k + 1));*///review this part
			//	if (list[j] == temp.substr(0, k + 1) + ".screen")
			//	{
			//		j++;//exists
			//	}
			//	else
			//	{
			//		stepOrResult.getListOfFiles().erase(stepOrResult.getListOfFiles().begin() + i);
			//		stepOrResult.decreaseNumOfMaps();
			//		i--;
			//	}
			//	k = 0;
			//}

			/*
			MAYBE ERROR AND CLOSE GAME OR CHECK MATCHES AND PLAY ONLY THE GOOD MATCHES
			*/
		}
		else
		{
			//check if names of all files are matching
			//strcompare untill the "."
			string temp;
			int k = 0;
			int j = 0;
			for (int i = 0; i < numOfMaps; i++)
			{
				temp.clear();
				temp = stepOrResult.getListOfFiles()[i];
				while (temp[k] != '.')
				{
					k++;
				}
				/*newList.push_back(temp.substr(0, k + 1));*///review this part
				if (list[i] == temp.substr(0, k + 1) + ".screen")
				{
					j++;//exists
				}
				else
				{
					/*
						MAYBE ERROR AND CLOSE GAME OR CHECK MATCHES AND PLAY ONLY THE GOOD MATCHES
					*/
					/*stepOrResult.getListOfFiles().erase(stepOrResult.getListOfFiles().begin() + i);
					stepOrResult.decreaseNumOfMaps();
					i--;*/
				}
				k = 0;
			}
		}
	}
	else if (input.cmdOptionExists("-save"))
	{

		//erase all files and create matching ones
		vector<string> newList;
		//int k=0;
		string temp;
		for (int i = 0; i < numOfMaps; i++)
		{
			temp.clear();
			temp = getListOfFiles()[i];
			std::size_t pos = temp.find(".screen");
			newList.push_back(temp.substr(0,pos));//review this part
			//while (temp[k]!='.')
			//{
			//	k++;
			//}
			//newList.push_back(temp.substr(0, k + 1));//review this part
			if (fileType==FileType::steps)
			{
				newList[i] = newList[i] + ".steps";
			}
			else
				newList[i] = newList[i] + ".result";
			stepOrResult.setListOfFiles(newList);
			//k = 0;
		}
		// OR
		//if (stepOrResult.getNumOfMaps() == 0)
		//{
		//	//no matching files Create them
		//}
		//else if (numOfMaps != stepOrResult.getNumOfMaps())
		//{
		//	//erase all files and create matching ones;
		//}
		//else
		//{
		//	//check if names of all files are matching
		//	//if a file doesn't match' erase and create one that matches
		//	//strcompare untill the "."
		//}
	}

}


