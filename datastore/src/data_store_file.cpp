#include <string>
#include <fstream>
#include <sstream>

#include "../includes/data_store_file.h"

using namespace std;
//pass in a crypto object and it will be used to en/decrypt data
//don't, and data stored in clear
DataStore_File::DataStore_File(string fileName, Crypto* crypto):DataStore(crypto),
		myFileName(fileName)
{

}

DataStore_File::~DataStore_File(void)
{

}

string getStringFromSerialization(string myString)
{
	string temp = "";

	for(unsigned int i=0;i<myString.length();i++)
	{
		if(myString[i] == ',')
		{
			temp = myString.substr(0,i);
			break;
		}
	}

	return temp;
}

int getCountFromSerialization(string myString)
{
	int temp = 1;

	for(unsigned int i=0;i<myString.length();i++)
	{
		if(myString[i] == ',')
		{
			temp = std::stoi(myString.substr(i+1));
			break;
		}
	}
	return temp-1;
}

//load from file myFileName, if present, use the crypto object to decrypt
bool DataStore_File::load(std::vector<String_Data> &myVector)
{
	ifstream myinputstream;

	myinputstream.open(this->myFileName.c_str());

	if(myinputstream.is_open())
	{
		string line;
		while(!myinputstream.eof())
		{
			getline(myinputstream, line);
			if(line != "" && line != " ")
			{
				decrypt(line);
				String_Data temp = String_Data(getStringFromSerialization(line));
				for(int i=0;i<getCountFromSerialization(line);i++)
					temp.increment();
				myVector.push_back(temp);
			}
		}

		myinputstream.close();
	}
	return false;
}

//save to file myFileName, if present, use the crypto object to encrypt
//I extracted one entry of the vector at a time and then encrypted it
//if crypto object present, saved this to disk and then sent a std::endl
//so each entry is encrypted, but you can count the number of entries
//by the number of lines in the file
bool DataStore_File::save(std::vector<String_Data> &myVector)
{
	ofstream myoutputstream;

	myoutputstream.open(this->myFileName.c_str());

	if(myoutputstream.is_open())
	{
		for(unsigned int i = 0; i<myVector.size();i++)
		{
			if(myVector[i].serialize() != "" && myVector[i].serialize() != " ")
			{
				String_Data tempData = myVector[i];
				string tempStr = tempData.serialize();
				encrypt(tempStr);
				myoutputstream << tempStr << endl;;
			}
		}

		myoutputstream.close();
	}
	return false;
}

bool DataStore_File::openFile(std::fstream& myfile,
		const std::string& myFileName, std::ios_base::openmode mode)
{
	myfile.open(myFileName.c_str(), mode);
	if(myfile.is_open())
	{
		return true;
	}

	return false;
}

void DataStore_File::closeFile(std::fstream& myfile)
{
	if(myfile.is_open())
		myfile.close();
}


