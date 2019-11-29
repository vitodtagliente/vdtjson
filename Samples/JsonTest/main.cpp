#include <iostream>
#include <vdtjson/number.h>

using namespace std;
using namespace json;

int main()
{
	int c = 5;
	int d = c++;

	json::number a{ 3 };
	++a;
	a++;
	number b = a++;
	--a;
	a *= 2;
	a = 4;
	a = 3.5f;
	a = 4.0;

	cout << "Premi un tasto per continuare...";
	return getchar();
}