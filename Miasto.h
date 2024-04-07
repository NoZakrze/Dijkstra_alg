#include <iostream>
using namespace std;

class Miasto
{
	friend class Graf;
private:
	char* nazwa;
	int hash;
	Miasto* nastepny;
public:
	Miasto(int hash, char* nazwa, int dlugosc);
	~Miasto()
	{
		delete[] nazwa;
	}
};