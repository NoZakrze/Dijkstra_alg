#include "Graf.h"
#include "Kolejka.h"
#include <cstdio>
using namespace std;

Graf::Graf()
{
	cin >> n >> m;
	int bin = getchar();
	mapa = new char* [m];
	for (int i = 0; i < m; i++)
	{
		mapa[i] = new char[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mapa[i][j] = getchar();
			
			if (mapa[i][j] == '*')
			{
				wezly++;
				DodajLokacje(j, i);
			}
			
		}
		bin = getchar();
	}
	tab = new Wezel * [wezly];
	miasta = new Miasto * [wezly];
	for (int i = 0; i < wezly; i++)
	{
		tab[i] = NULL;
		miasta[i] = NULL;
	}
}
void Graf::Operacje()
{
	wczytanieWezlow();
	WczytanieLotow();
	SzukajSasiadow();
	WczytanieKomend();
}
void Graf::wczytanieWezlow()
{
	Lokacja* tmp = pierwszy;
	while(tmp)
	{
		int x, y;
		int i = tmp->y, j = tmp->x;
		znajdzNazwe(x, y, i, j);
		while (x >= 0 && czyLitera(mapa[y][x - 1]))
			x--;
		char nazwa[64];
		int d = 0;
		while (czyLitera(mapa[y][x]))
		{
			nazwa[d] = mapa[y][x];
			x++;
			d++;
		}
		nazwa[d] = '\0';
		dodajWezel(j, i, nazwa, d + 1);
		dodajMiasto(j, i, nazwa, d + 1);
		tmp = tmp->nastepny;
	}
	
}
void Graf::dodajWezel(int x, int y, char* nazwa, int dlugosc)
{
	Wezel* nowy = new Wezel(x, y, nazwa, n, dlugosc);
	int indeks = (nowy->hash) % wezly;
	Wezel* tmp = tab[indeks];
	if (tmp == NULL)
		tab[indeks] = nowy;
	else
	{
		while (tmp->nastepny)
			tmp = tmp->nastepny;
		tmp->nastepny = nowy;
	}
}
void Graf::dodajMiasto(int x, int y, char* nazwa, int dlugosc)
{
	int hash = hashPolozenie(x, y);
	int hash_n = hashNazwa(nazwa);
	Miasto* nowe = new Miasto(hash, nazwa, dlugosc);
	int indeks = hash_n % wezly;
	Miasto* tmp = miasta[indeks];
	if (tmp == NULL)
		miasta[indeks] = nowe;
	else
	{
		while (tmp->nastepny)
			tmp = tmp->nastepny;
		tmp->nastepny = nowe;
	}
}
int Graf::hashPolozenie(int x, int y)
{
	return n * y + x;
}
int Graf::hashNazwa(char* nazwa)
{
	int i = 1, suma = nazwa[0], k = 0;
	while (nazwa[i] != '\0')
	{
		suma = suma + i * nazwa[i];
		i++;
	}
	return suma;
}
bool Graf::czyLitera(char a)
{
	if (a >= '0' && a <= 'Z')
		return true;
	else
		return false;
}
void Graf::znajdzNazwe(int& x, int& y, int i, int j)
{
	int tx[BOKI], ty[BOKI];
	for (int k = -1, h = 0; k <= 1; k++, h = h + 3)
	{
		tx[h] = k + j;
		tx[h + 1] = k + j;
		tx[h + 2] = k + j;
	}
	for (int h = 0; h < BOKI; h = h + 3)
	{
		ty[h] = -1 + i;
		ty[h + 1] = 0 + i;
		ty[h + 2] = 1 + i;
	}
	for (int k = 0; k < BOKI; k++)
	{
		if (tx[k] >= 0 && tx[k] < n && ty[k] >= 0 && ty[k] < m)
		{
			if (czyLitera(mapa[ty[k]][tx[k]]))
			{
				bool a = 0, b = 0;
				if (tx[k] > 0)
					a = czyLitera(mapa[ty[k]][tx[k] - 1]);
				if (tx[k] < n - 1)
					b = czyLitera(mapa[ty[k]][tx[k] + 1]);
				if (a == 0 || b == 0)
				{
					x = tx[k];
					y = ty[k];
					break;
				}
			}
		}
	}
}
void Graf::SzukajSasiadow()
{
	for (int i = 0; i < wezly; i++)
	{
		Wezel* tmp = tab[i];
		while (tmp)
		{
			Sasiedzi(tmp);
			tmp = tmp->nastepny;
		}
	}

}
void Graf::Sasiedzi(Wezel* miasto)
{
	bool** bmapa = new bool* [m];
	for (int i = 0; i < m; i++)
	{
		bmapa[i] = new bool[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bmapa[i][j] = 0;
		}
	}
	Kolejka* kolejka = new Kolejka();
	bmapa[miasto->y][miasto->x] = 1;
	kolejka->Dodaj(miasto->x,miasto->y,0);
	while (!kolejka->CzyPusta())
	{
		Punkt* tmp = kolejka->pierwszy;
		int x = tmp->x;
		int y = tmp->y;
		if (mapa[y][x] == '*' && tmp->d>0)
		{
				miasto->DodajSasiada(hashPolozenie(x, y), tmp->d);
		}
		else 
		{
			if (x > 0)
			{
				if ((mapa[y][x - 1] == '#' || mapa[y][x - 1]=='*') && bmapa[y][x - 1] == 0)
				{
					kolejka->Dodaj(x - 1, y, (tmp->d) + 1);
					bmapa[y][x - 1] = 1;
				}
			}
			if (y > 0)
			{
				if ((mapa[y - 1][x] == '#' || mapa[y - 1][x] == '*') && bmapa[y - 1][x] == 0)
				{
					kolejka->Dodaj(x, y - 1, (tmp->d) + 1);
					bmapa[y - 1][x] = 1;
				}
			}
			if (x < n - 1)
			{
				if ((mapa[y][x + 1] == '#' || mapa[y][x + 1] == '*') && bmapa[y][x + 1] == 0)
				{
					kolejka->Dodaj(x + 1, y, (tmp->d) + 1);
					bmapa[y][x + 1] = 1;
				}
			}
			if (y < m - 1)
			{
				if ((mapa[y + 1][x] == '#' || mapa[y + 1][x] == '*') && bmapa[y + 1][x] == 0)
				{
					kolejka->Dodaj(x, y + 1, (tmp->d) + 1);
					bmapa[y + 1][x] = 1;
				}
			}
		}
		kolejka->Usun();
	}
	for (int i = 0; i < m; i++)
	{
		delete[] bmapa[i];
	}
	delete[] bmapa;
	delete kolejka;
}
bool Graf::Porownaj_napis(char* t, char* t2)
{
	int i = 0;
	while (t[i] != '\0' && t2[i] != '\0')
	{
		if (t[i] != t2[i])
			return false;
		i++;

	}
	if (t[i] != '\0' || t2[i] != '\0')
		return false;
	return true;
}
void Graf::Dijkstra(char* start, char* koniec, bool posrednie)
{
	DaneDijkstra** wyniki = new DaneDijkstra * [wezly];
	char** miastaPosrednie = new char* [wezly];
	for (int i = 0; i < wezly; i++)
	{
		miastaPosrednie[i] = new char[100];
	}
	for (int i = 0; i < wezly; i++)
	{
		wyniki[i] = NULL;
	}
	for (int i = 0; i < wezly; i++)
	{
		Wezel* tmp = tab[i];
		while (tmp)
		{
			DaneDijkstra* nowy = new DaneDijkstra(tmp->hash);
			DaneDijkstra* tmp1 = wyniki[i];
			if (wyniki[i] == NULL)
				wyniki[i] = nowy;
			else
			{
				while (tmp1->nastepny)
				{
					tmp1 = tmp1->nastepny;
				}
				tmp1->nastepny = nowy;
			}
			tmp = tmp->nastepny;
		}
	}
	int hashstart = ZwrocHashpolozenia(start);
	DaneDijkstra* tmp = wyniki[hashstart % wezly];
	while (tmp)
	{
		if (hashstart == tmp->hash)
		{
			tmp->odleglosc = 0;
			break;
		}
		tmp = tmp->nastepny;
	}
	for (int i = 0; i < wezly; i++)
	{
		DaneDijkstra* min = Najmniejszy(wyniki, wezly);
		if (min == NULL)
		{
			break;
		}
		min->odwiedzony = true;
		Wezel* obecny = GetWezel(min->hash, tab, wezly);
		Sasiad* tmp = obecny->pierwszy;
		while (tmp)
		{
			DaneDijkstra* tmp1 = DaneSasiada(wyniki, tmp->hash, wezly);
			if (tmp1->odwiedzony == false)
			{
				if (tmp1->odleglosc > min->odleglosc + tmp->droga)
				{
					tmp1->odleglosc = min->odleglosc + tmp->droga;
					tmp1->pophash = min->hash;
				}
			}
			tmp = tmp->nastepny;
		}
	}
	int hashodp = ZwrocHashpolozenia(koniec);
	DaneDijkstra* wynik = DaneSasiada(wyniki, hashodp, wezly);
	if (!posrednie)
	{
		cout << wynik->odleglosc << endl;
	}
	else
	{
		cout << wynik->odleglosc << " ";
		int pop = wynik->pophash, i = 0;
		bool cokolwiek = 0;
		Wezel* poprzednik;
		if (pop != -1)
		{
			while (DaneSasiada(wyniki, pop, wezly)->pophash != -1)
			{
				Wezel* poprzedni = GetWezel(pop, tab, wezly);
				if (poprzedni->nazwa[0] != '\0')
				{
					miastaPosrednie[i] = poprzedni->nazwa;
					i++;
					cokolwiek = 1;
				}
				pop = DaneSasiada(wyniki, pop, wezly)->pophash;
			}
			i--;
		}
		while (i >= 0 && cokolwiek)
		{
			cout << miastaPosrednie[i];
			if (i > 0)
				cout << " ";
			i--;
		}
	}
	for (int i = 0; i < wezly; i++)
	{
		if (wyniki[i] != NULL)
		{
			DaneDijkstra* obecny = wyniki[i];
			DaneDijkstra* nastepny = NULL;
			while (obecny)
			{
				nastepny = obecny->nastepny;
				delete obecny;
				obecny = nastepny;
			}
		}
	}

	for (int h = 0; h < wezly; h++)
	{
		if (miastaPosrednie[h] != NULL)
		{
			miastaPosrednie[h] = nullptr;
			delete[] miastaPosrednie[h];
		}
	}

	delete[] wyniki;
	delete[] miastaPosrednie;
	cout << endl;
}
int Graf::ZwrocHashpolozenia(char* nazwa)
{
	int hash = hashNazwa(nazwa);
	Miasto* tmp = miasta[hash % wezly];
	while (tmp)
	{
		if (Porownaj_napis(nazwa, tmp->nazwa))
			return tmp->hash;
		tmp = tmp->nastepny;
	}
	return hash;
}
DaneDijkstra* Graf::Najmniejszy(DaneDijkstra** tablica, int rozmiar)
{
	int najmniejszy = NIESKONCZONOSC - 1;
	DaneDijkstra* wynik = NULL;
	for (int i = 0; i < rozmiar; i++)
	{
		DaneDijkstra* tmp = tablica[i];
		while (tmp)
		{
			if (tmp->odleglosc < najmniejszy && tmp->odwiedzony == false)
			{
				najmniejszy = tmp->odleglosc;
				wynik = tmp;
			}
			tmp = tmp->nastepny;
		}
	}
	return wynik;

}
Wezel* Graf::GetWezel(int hash, Wezel** tablica, int rozmiar)
{
	Wezel* wynik = NULL;
	Wezel* tmp = tablica[hash % rozmiar];
	while (tmp)
	{
		if (tmp->hash == hash)
		{
			return tmp;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}
DaneDijkstra* Graf::DaneSasiada(DaneDijkstra** tablica, int hash, int rozmiar)
{
	DaneDijkstra* wynik = NULL;
	DaneDijkstra* tmp = tablica[hash % rozmiar];
	while (tmp)
	{
		if (tmp->hash == hash)
		{
			return tmp;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}
void Graf::WczytanieLotow()
{
	int a, i;
	cin >> a;
	char bin = getchar();
	char bufor[BUFOR];
	for (int f = 0; f < a; f++)
	{
		bool flaga = 1;
		i = 0;
		while (flaga)
		{
			char s = getchar();
			if (s == '\n' || s == EOF)
				flaga = 0;
			else
			{
				bufor[i] = s;
				i++;
			}
		}
		bufor[i] = '\0';
		char start[100], koniec[100], droga[32];
		i = 0;
		while (bufor[i] != ' ')
		{
			start[i] = bufor[i];
			i++;
		}
		start[i] = '\0';
		i++;
		int j = 0;
		while (bufor[i] != ' ')
		{
			koniec[j] = bufor[i];
			i++;
			j++;
		}
		koniec[j] = '\0';
		i++;
		j = 0;
		while (bufor[i] != '\0')
		{
			droga[j] = bufor[i];
			i++;
			j++;
		}
		droga[j] = '\0';
		Wezel* tmp = GetWezel(ZwrocHashpolozenia(start), tab, wezly);
		tmp->DodajSasiada(ZwrocHashpolozenia(koniec), StringNaInt(droga));
	}
}
int Graf::StringNaInt(char* napis)
{
	int wynik = 0, i = 0;
	while (napis[i] != '\0')
	{
		int tmp = napis[i] - 48;
		wynik = wynik * 10 + tmp;
		i++;
	}
	return wynik;
}
void Graf::WczytanieKomend()
{
	int a, i;
	cin >> a;
	char bin = getchar();
	char bufor[BUFOR];
	for (int f = 0; f < a; f++)
	{
		bool flaga = 1;
		i = 0;
		while (flaga)
		{
			char s = getchar();
			if (s == '\n' || s == EOF)
				flaga = 0;
			else
			{
				bufor[i] = s;
				i++;
			}
		}
		bufor[i] = '\0';
		char start[100], koniec[100];
		bool trasa;
		i = 0;
		while (bufor[i] != ' ')
		{
			start[i] = bufor[i];
			i++;
		}
		start[i] = '\0';
		i++;
		int j = 0;
		while (bufor[i] != ' ')
		{
			koniec[j] = bufor[i];
			i++;
			j++;
		}
		koniec[j] = '\0';
		i++;
		trasa = bufor[i] - '0';
		Dijkstra(start, koniec, trasa);
	}
}
void Graf::DodajLokacje(int x, int y)
{
	Lokacja* nowy = new Lokacja(x, y);
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
Graf::~Graf()
{
	for (int i = 0; i < m; i++)
	{
		delete[] mapa[i];
	}
	delete[] mapa;

	for (int i = 0; i < wezly; i++)
	{
		if (tab[i] != NULL)
		{
			Wezel* obecny = tab[i];
			Wezel* nastepny = NULL;
			while (obecny)
			{
				nastepny = obecny->nastepny;
				delete obecny;
				obecny = nastepny;
			}
		}
	}
	delete[] tab;
	for (int i = 0; i < wezly; i++)
	{
		if (miasta[i] != NULL)
		{
			Miasto* obecny = miasta[i];
			Miasto* nastepny = NULL;
			while (obecny)
			{
				nastepny = obecny->nastepny;
				delete obecny;
				obecny = nastepny;
			}
		}
	}
	delete[] miasta;
	Lokacja* obecny = pierwszy;
	Lokacja* kolejny = 0;
	while (obecny != 0)
	{
		kolejny = obecny->nastepny;
		delete obecny;
		obecny = kolejny;
	}

}
