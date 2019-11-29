#include <iostream>
#include <vdtjson/number.h>

using namespace std;

int main()
{
	json::number a{ 3 };
	++a;
	--a;
	a *= 2;

	cout << "Premi un tasto per continuare...";
	return getchar();
}