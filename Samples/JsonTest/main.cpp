#include <iostream>
#include <vdtjson/json.h>

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
	a += 3;
	(a += 5.0f) *= 5;

	json::value v({ value("ciao"), value(2), value(3.4f) });
	json::value ciao("ciao");


	cout << endl << json::to_string(a);
	cout << endl << json::to_string(ciao);
	cout << endl << json::to_string(v);

	cout << "Premi un tasto per continuare...";
	return getchar();
}