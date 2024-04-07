#include <iostream>
using namespace std;

class Sasiad
{
	friend class Graf;
	friend class Wezel;
private:
	int hash, droga, hashStart;
	Sasiad* nastepny;
public:
	Sasiad(int hash, int droga, int hashStart)
		:nastepny(NULL), hash(hash), hashStart(hashStart), droga(droga)
	{};
	~Sasiad(){}
};