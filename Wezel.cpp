#include "Wezel.h"
using namespace std;

Wezel::Wezel(int x, int y, char* nazwa, int rozmiar, int dlugosc)
	:x(x), y(y), nastepny(NULL), pierwszy(NULL)
{
	hash = rozmiar * y + x;
	char* war = new char[dlugosc];
	int i = 0;
	do
	{
		war[i] = nazwa[i];
	} while (nazwa[i++] != '\0');
	this->nazwa = war;
}
void Wezel::DodajSasiada(int hash, int droga)
{
	if(hash!=this->hash)
	{
		Sasiad* nowy = new Sasiad(hash, droga, this->hash);
		Sasiad* tmp = pierwszy;
		if (tmp == NULL)
			pierwszy = nowy;
		else
		{
			while (tmp->nastepny)
				tmp = tmp->nastepny;
			tmp->nastepny = nowy;
		}
	}
}