#include "../includes/string_database.h"

using namespace std;

String_Database::String_Database(void)
{

}

String_Database::~String_Database(void)
{

}

string getStringFromString_Data(string myString)
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

//if not seen yet then add myString to myStrings
//otherwise increment the count for myString
void String_Database::add(std::string &myString)
{
	bool found = false;

	//isn't myStringsIter a global so should it be locked by a mutex?
	//should i even use the iterator
	for(unsigned int i=0;i<myStrings.size();i++)
	{
		if(myString == getStringFromString_Data(myStrings[i].serialize()))
		{
			//does this increment need to be locked?
			mutex.lock();
			myStrings[i].increment();
			mutex.unlock();
			found = true;
		}
	}

	if(!found)
	{
		mutex.lock();
		myStrings.push_back(String_Data(myString));
		mutex.unlock();
	}
}

//get number of times myString has been seen (or added with add)
int String_Database::getCount(std::string &myString)
{
	for(unsigned int i=0;i<myStrings.size();i++)
	{
		if(myString == getStringFromString_Data(myStrings[i].serialize()))
		{
			mutex.lock();
			return this->myStrings[i].getCount();
			mutex.unlock();
		}
	}

	return 0;
}

//clear the myStrings vector
void String_Database::clear()
{
	this->myStrings.clear();
}

//load from datastore, returns
//false if myDataStore = 0
//otherwise returns myDataStore->load results
bool String_Database::load(DataStore  *myDataStore)
{
	if(!myDataStore)
		return false;
	else
	{
		mutex.lock();
		myDataStore->load(myStrings);
		mutex.unlock();
	}
	return true;
}

//save to datastore,returns
//false if myDataStore = 0
//otherwise returns myDataStore->save results
bool String_Database::save(DataStore *myDataStore)
{
	if(!myDataStore)
		return false;
	else
	{
		mutex.lock();
		myDataStore->save(myStrings);
		mutex.unlock();
	}
	return true;
}


