#include <iostream>
#include "Graf.h"
using namespace std;
int main()
{
	Graf* graf = new Graf();
	graf->Operacje();
	delete graf;
	return 0;
}