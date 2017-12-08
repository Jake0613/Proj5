//============================================================================
// Name        : MED_Tester.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>
#include <string>

#include "../crypto/includes/crypto_AES.h"
#include "../stringdatabase/includes/string_database.h"
#include "../datastore/includes/data_store.h"

using namespace std;
//I've provided some hints in the form of comments and commented out code
//use them if you wish

////global database object 
String_Database myGlobalCache;

bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2,
		Crypto *pCrypto) {
	DataStore_File myDataStore_File1(MYFILE1, pCrypto);

	string temp1 = "Here";
	string temp2 = "Here2";
	string temp3 = "Here";
	myGlobalCache.add(temp1);
	myGlobalCache.add(temp2);
	myGlobalCache.add(temp3);

	myGlobalCache.save(&myDataStore_File1);

	//clear cache
	myGlobalCache.clear();
	std::cout<<"Clearing Cache\n";

	//load it
	myGlobalCache.load(&myDataStore_File1);
	std::cout<<"Loading from file "+ MYFILE1 +" \n";

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2, pCrypto);
	myGlobalCache.save(&myDataStore_File2);
	std::cout<<"Saving to file "+ MYFILE2 +" \n";

	//I use my own objects here to compare the files
	return true;
}

int main() {

	const string file1 = "./file1";
	const string file2 = "./file2";
	//I created and ran a bunch(20) of threads that added different strings to a string_database instance

	//Then I waited for all of them to finish so my program did not crash

	//Then I went through my string_database instance and made sure that it held the correct data

	//then I tested  serialization
	//first without encryption, 
	testSerialization(file1, file2, NULL);

	//then with
	Crypto_AES myCrypto("I Like Rollos   ");
	//testSerialization(ENCRYPT_FILE1, ENCRYPT_FILE2, &myCrypto);
}
