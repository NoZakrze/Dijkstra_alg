#include <iostream>
#include "Wezel.h"
#include "Miasto.h"
#define BOKI 9
#define NIESKONCZONOSC 1000000
#define BUFOR 256
using namespace std;

struct DaneDijkstra
{
	int hash, odleglosc, pophash;
	bool odwiedzony;
	DaneDijkstra* nastepny;
	DaneDijkstra(int hash)
		: hash(hash), odwiedzony(false), pophash(-1), odleglosc(NIESKONCZONOSC), nastepny(NULL)
	{}
};
struct Lokacja
{
	int x, y;
	Lokacja* nastepny;
	Lokacja(int x, int y)
		:x(x), y(y), nastepny(NULL)
	{};
};
class Graf
{
private:
	char** mapa;
	int n, m, wezly = 0;
	Wezel** tab;
	Miasto** miasta;
	Lokacja* pierwszy = NULL;
	Lokacja* ostatni = NULL;
public:
	Graf();
	void Operacje();
	void wczytanieWezlow();
	void dodajWezel(int x, int y, char* nazwa, int dlugosc);
	void dodajMiasto(int x, int y, char* nazwa, int dlugosc);
	int hashPolozenie(int x, int y);
	int hashNazwa(char* nazwa);
	bool czyLitera(char a);
	void znajdzNazwe(int& x, int& y, int i, int j);
	void SzukajSasiadow();
	void Sasiedzi(Wezel* miasto);
	bool Porownaj_napis(char* t, char* t2);
	void Dijkstra(char* start, char* koniec, bool posrednie);
	int ZwrocHashpolozenia(char* nazwa);
	Wezel* GetWezel(int hash, Wezel** tablica, int rozmiar);
	DaneDijkstra* Najmniejszy(DaneDijkstra** tablica, int rozmiar);
	DaneDijkstra* DaneSasiada(DaneDijkstra** tablica, int hash, int rozmiar);
	void WczytanieLotow();
	int StringNaInt(char* napis);
	void WczytanieKomend();
	void DodajLokacje(int x, int y);
	~Graf();
};

