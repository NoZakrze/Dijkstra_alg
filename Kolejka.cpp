#include "Kolejka.h"
using namespace std;

bool Kolejka::CzyPusta()
{
	if (pierwszy)
		return false;
	else
		return true;
}
void Kolejka::Dodaj(int x, int y, int d)
{
	Punkt* nowy = new Punkt(x, y, d);
	if (!pierwszy)
	{
		pierwszy = nowy;
		ostatni = nowy;
	}
	else
	{
		ostatni->nastepny = nowy;
		ostatni = nowy;
	}
}
void Kolejka::Usun()
{
	if (!CzyPusta())
	{
		if (pierwszy->nastepny)
		{
			Punkt* usuwany = pierwszy;
			pierwszy = pierwszy->nastepny;
			delete usuwany;
		}
		else
		{
			delete pierwszy;
			pierwszy = NULL;
			ostatni = NULL;
		}
	}
}