#include <iostream>
using namespace std;

struct Punkt {
	int x, y, d;
	Punkt* nastepny;
	Punkt(int x, int y, int d)
		: x(x), y(y), d(d), nastepny(NULL)
	{}
};

class Kolejka
{
	friend class Graf;
private:
	Punkt* pierwszy, *ostatni;
public:
	Kolejka()
		: pierwszy(NULL), ostatni(NULL)
	{};
	bool CzyPusta();
	void Dodaj(int x, int y, int d);
	void Usun();
	~Kolejka() {};
};