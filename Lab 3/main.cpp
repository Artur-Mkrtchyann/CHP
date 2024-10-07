#include "Cesar.h"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstddef>

using namespace std;

#define BUF_SIZE  1024

//
//const char* encode_arr = "1234567890-=!@#$%^&*()_+\
//qwertyuiop[]QWERTYUIOP{}\
//asdfghjkl;ASDFGHJKL:\
//zxcvbnm,./ZXCVBNM<>?";
//
//const char* decode_arr = "=-0987654321+_)(*&^%$#@!\
//][poiuytrewq}{POIUYTREWQ\
//;lkjhgfdsa:LKJHGFDSA\
///.,mnbvcxz?><MNBVCXZ";


unsigned char encode_arr[TemplateSize];
unsigned char decode_arr[TemplateSize];

int InitTemplateKeytable(unsigned char *enc_arr, unsigned char * dec_arr, unsigned int TemplateSize)
{
	cout << "\nInitTemplateKeytable\n";

	if (!encode_arr || !decode_arr || !TemplateSize)
		return -1;
	unsigned int i;
	for (i = 0; i < TemplateSize; ++i)
	{
		dec_arr[i] = encode_arr[i] = i;
	}

	// To obtain a time-based seed
	unsigned seed = 0;
	shuffle(dec_arr, dec_arr + TemplateSize , default_random_engine(seed));
	//std::swap(dec_arr[1], dec_arr[128]);

	unsigned int hh;
	for (i = 0; i < TemplateSize; ++i)
	{
		if (i == 127)
		{
			hh = (unsigned int)encode_arr[i];
			hh = (unsigned int)encode_arr[i];

		}

		hh = (unsigned int)encode_arr[i];
		cout << (unsigned int)encode_arr[i] << ' ';
	}

	cout << "\n\nShuffle \n\n";

		for (i = 0; i < TemplateSize; ++i)
		{
			cout << (unsigned int)decode_arr[i] << ' ';
		}

	cout << "\n\nEnd\n\n";
	return 0;

}


int main()
{
	unsigned char src[BUF_SIZE], dest[BUF_SIZE] , decrypt[BUF_SIZE];

	std::string str("This is an apple");
	unsigned int size = (unsigned int)str.size();

	strcpy((char *)src, str.c_str());

	std::cout << "Text to encrypt:\n" << src << endl;

	InitTemplateKeytable(encode_arr, decode_arr, TemplateSize);

	Cesar obj;

	obj.SetTemplateTable(encode_arr, decode_arr, TemplateSize);

	if (obj.Encrypt(src, size, dest, size))
	{
		cout << "Failed to Encrypt...\n";
		return -1;
	}

	dest[size] = 0;
	std::cout << dest << endl;
	if( obj.Decrypt(dest, size, decrypt, size) )
	{
		cout << "Failed to Decrypt...\n";
		return -2;
	}

	decrypt[size] = 0;
	std::cout << decrypt << endl;

	if (strcmp((const char*)src, (const char*)decrypt))
	{
		cout << "Failed" << endl;
	}
	else
		cout << "Success" << endl;

	return 0;
}