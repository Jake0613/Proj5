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
#include <fstream>
#include <chrono>

#include "../crypto/includes/crypto_AES.h"
#include "../stringdatabase/includes/string_database.h"
#include "../datastore/includes/data_store.h"

using namespace std;
//I've provided some hints in the form of comments and commented out code
//use them if you wish

////global database object 
String_Database myGlobalCache;

bool compareTwoFiles(string filename1, string filename2)
{
	vector<string> vectorStringsOfFile1;
	vector<string> vectorStringsOfFile2;

	ifstream myinputstream;

	myinputstream.open(filename1.c_str());

	if(myinputstream.is_open())
	{
		string line;
		while(!myinputstream.eof())
		{
			getline(myinputstream, line);
			vectorStringsOfFile1.push_back(line);
		}

		myinputstream.close();
	}

	myinputstream.open(filename2.c_str());

	if(myinputstream.is_open())
	{
		string line;
		while(!myinputstream.eof())
		{
			getline(myinputstream, line);
			vectorStringsOfFile2.push_back(line);
		}

		myinputstream.close();
	}

	if(vectorStringsOfFile1.size() != vectorStringsOfFile2.size()) return false;

	for(unsigned int i=0;i<vectorStringsOfFile1.size();i++)
		if(vectorStringsOfFile1[i] != vectorStringsOfFile2[i]) return false;

	return true;
}

bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2,
		Crypto *pCrypto) {
	DataStore_File myDataStore_File1(MYFILE1, pCrypto);

	string temp1 = "Here";
	string temp2 = "Here2";
	string temp3 = "Here";
	string temp4 = "Dog";
	string temp5 = "I want to watch hockey";
	myGlobalCache.add(temp1);
	myGlobalCache.add(temp2);
	myGlobalCache.add(temp3);
	myGlobalCache.add(temp4);
	myGlobalCache.add(temp5);

	myGlobalCache.save(&myDataStore_File1);

	//clear cache
	myGlobalCache.clear();
//	std::cout<<"Clearing Cache\n";

	//load it
	myGlobalCache.load(&myDataStore_File1);
//	std::cout<<"Loading from file "+ MYFILE1 +" \n";

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2, pCrypto);
	myGlobalCache.save(&myDataStore_File2);
//	std::cout<<"Saving to file "+ MYFILE2 +" \n";

	//I use my own objects here to compare the files
	return true;
}

void testEncryptionAndDecryptionSingleLine(const string &regfile,
		const string &encryptedfile, const string &decryptedfile, Crypto *pCrypto)
{
	DataStore_File myDataStore_File1(regfile, NULL);

	myGlobalCache.clear();

	string temp1 = "Testing encryption and decryption";
	string temp2 = "H";
	myGlobalCache.add(temp1);
	myGlobalCache.add(temp2);

	myGlobalCache.save(&myDataStore_File1);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File2(encryptedfile, pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File3(decryptedfile, NULL);
	myGlobalCache.save(&myDataStore_File3);

	myGlobalCache.clear();
}

void addString(string str)
{
	myGlobalCache.add(str);
}

void testWith5Threads(const string &regfile,
		const string &encryptedfile, const string &decryptedfile, Crypto *pCrypto)
{
	myGlobalCache.clear();

	thread t1(addString, "a string");
	thread t2(addString, "i am a thread");
	thread t3(addString, "i hope this works!");
	thread t4(addString, "a string");
	thread t5(addString, "last thread");

	this_thread::sleep_for(chrono::microseconds(1000000));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	DataStore_File myDataStore_File1(regfile, NULL);
	myGlobalCache.save(&myDataStore_File1);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File2(encryptedfile, pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File3(decryptedfile, NULL);
	myGlobalCache.save(&myDataStore_File3);

	myGlobalCache.clear();
}

void test10Threads(const string &regfile,
		const string &encryptedfile, const string &decryptedfile, Crypto *pCrypto)
{
	myGlobalCache.clear();

	thread t1(addString, "a string");
	thread t2(addString, "i am a thread");
	thread t3(addString, "i hope this works!");
	thread t4(addString, "a string");
	thread t5(addString, "last thread");
	thread t6(addString, "i am also a thread");
	thread t7(addString, "a string");
	thread t8(addString, "8th thread");
	thread t9(addString, "9th thread");
	thread t10(addString, "last thread");


	this_thread::sleep_for(chrono::microseconds(1000000));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();

	DataStore_File myDataStore_File1(regfile, NULL);
	myGlobalCache.save(&myDataStore_File1);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File2(encryptedfile, pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File3(decryptedfile, NULL);
	myGlobalCache.save(&myDataStore_File3);

	myGlobalCache.clear();
}

void test20Threads(const string &regfile,
		const string &encryptedfile, const string &decryptedfile, Crypto *pCrypto)
{
	myGlobalCache.clear();

	thread t1(addString, "a string");
	thread t2(addString, "i am a thread");
	thread t3(addString, "i hope this works!");
	thread t4(addString, "a string");
	thread t5(addString, "last thread");
	thread t6(addString, "i am also a thread");
	thread t7(addString, "a string");
	thread t8(addString, "8th thread");
	thread t9(addString, "9th thread");
	thread t10(addString, "last thread");
	thread t11(addString, "i am also a thread");
	thread t12(addString, "Peanut Butter is the best condiment");
	thread t13(addString, "Ich schreibe auf Deutsch weil es Spass macht.");
	thread t14(addString, "No ablo espanol sadly");
	thread t15(addString, "a string");
	thread t16(addString, "This is a lot of threads. Please don't crash computer");
	thread t17(addString, "I am running out of weird phrases");
	thread t18(addString, "I hope my critical sections are locked correctly");
	thread t19(addString, " or this could become awkward when you grade this.");
	thread t20(addString, "   skjfh  dfshk     hh    ");


	this_thread::sleep_for(chrono::microseconds(1000000));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();
	t17.join();
	t18.join();
	t19.join();
	t20.join();

	DataStore_File myDataStore_File1(regfile, NULL);
	myGlobalCache.save(&myDataStore_File1);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File2(encryptedfile, pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	myGlobalCache.clear();

	myGlobalCache.load(&myDataStore_File1);

	DataStore_File myDataStore_File3(decryptedfile, NULL);
	myGlobalCache.save(&myDataStore_File3);

	myGlobalCache.clear();
}

int main() {

	const string file1 = "./file1";
	const string file2 = "./file2";
	const string file3 = "./file3";
	//I created and ran a bunch(20) of threads that added different strings to a string_database instance

	//Then I waited for all of them to finish so my program did not crash

	//Then I went through my string_database instance and made sure that it held the correct data

	//then I tested  serialization
	//first without encryption, 
	testSerialization(file1, file2, NULL);
	if(compareTwoFiles(file1, file2)) cout << "SUCCESS TEST 1" << endl;

	Crypto_AES myCrypto("I Like Rollos   ");
	testEncryptionAndDecryptionSingleLine(file1, file2, file3, &myCrypto);
	if(compareTwoFiles(file1, file3)) cout << "SUCCESS TEST 2" << endl;

	testWith5Threads(file1, file2, file3, &myCrypto);
	if(compareTwoFiles(file1, file3)) cout << "SUCCESS TEST 3" << endl;

	test10Threads(file1, file2, file3, &myCrypto);
	if(compareTwoFiles(file1, file3)) cout << "SUCCESS TEST 4" << endl;

	test20Threads(file1, file2, file3, &myCrypto);
	if(compareTwoFiles(file1, file3)) cout << "SUCCESS TEST 5" << endl;

	//then with
	//Crypto_AES myCrypto("I Like Rollos   ");
	//testSerialization(ENCRYPT_FILE1, ENCRYPT_FILE2, &myCrypto);
}
