#include "Miasto.h"
using namespace std;

Miasto::Miasto(int hash, char* nazwa, int dlugosc)
	:hash(hash), nastepny(NULL)
{
	char* war = new char[dlugosc];
	int i = 0;
	do
	{
		war[i] = nazwa[i];
	} while (nazwa[i++] != '\0');
	this->nazwa = war;
}