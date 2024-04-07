#include <iostream>
#include "Sasiad.h"
using namespace std;

class Wezel
{
	friend class Graf;
private:
	char* nazwa;
	int x, y, hash;
	Sasiad* pierwszy;
	Wezel* nastepny;
public:
	Wezel(int x, int y, char* nazwa,int rozmiar, int dlugosc);
	void DodajSasiada(int hash, int droga);
	~Wezel()
	{
		delete[] nazwa;
		Sasiad* obecny = pierwszy;
		Sasiad* nastepny = NULL;
		while (obecny)
		{
			nastepny = obecny->nastepny;
			delete obecny;
			obecny = nastepny;
		}
	}
};