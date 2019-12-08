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
	json::number b = a++;
	--a;
	a *= 2;
	a = 4;
	a = 3.5f;
	a = 4.0;
	a += 3;
	(a += 5.0f) *= 5;

	json::value v({ value("ciao"), value(2), value(3.4f) });
	json::value ciao("ciao");
	cout << ciao.size() << endl;

	auto obj = json::object();

	v = json::value::object_t{ {"name", value("vito domenico")}, {"surname", value("tagliente")} };

	// cout << endl << json::to_string(a);
	// cout << endl << json::to_string(ciao);
	cout << endl << json::to_string(v);

	// deserialization tests

	json::value little_bool = json::parse("true");
	little_bool = json::parse("    True ");
	little_bool = json::parse("FALSE   ");

	json::value little_number = json::parse("2.4");
	little_number = json::parse("   1 ");

	json::value little_string = json::parse("\"ciaoooo\"    ");

	json::value little_array = json::parse(" [1, \"ciao\", 4.5, true, null]");

	json::value little_obj = json::parse(" {\"name\": \"vito\", \"age\": 27} ");

	cout << "Premi un tasto per continuare...";
	return getchar();
}