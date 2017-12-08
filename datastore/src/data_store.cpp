#include "../includes/data_store.h"

using namespace std;
//pass in a crypto object and it will be used to en/decrypt data
//don't, and data stored in clear
DataStore::DataStore(Crypto* crypto):myCrypto(crypto)
{

}

DataStore::~DataStore(void)
{
	if(myCrypto)
		myCrypto = 0;
}

//ensures data is encrypted when stored
//will encrypt/decrypt if myCrypto is not null
//if myCrypto is null will store data in the clear
//think about what this means for the implementation of the following 2 functions
bool DataStore::encrypt(string &myString)
{
	bool answer = false;

	//DO NOT encrypt, myCrypto = null
	if(!this->myCrypto)
	{
		return answer = true;
	}
	//Store it encrypted
	else
	{
		myCrypto->encrypt(myString);
		return answer = true;
	}

	return answer;
}

bool DataStore::decrypt(string &myString)
{
	bool answer = false;

	//DO NOT encrypt, myCrypto = null
	if(!this->myCrypto)
	{
		return answer = true;
	}
	//Store it encrypted
	else
	{
		myCrypto->decrypt(myString);
		return answer = true;
	}

	return answer;
}
