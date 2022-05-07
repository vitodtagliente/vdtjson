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
	v.safeAt("foo").as_bool(false);

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

	json::value nested_obj = json::parse("{\"image\":\"222601788947200\",\"rect\":{\"x\":0.818182,\"width\":0.090909,\"y\":0.272727,\"height\":0.090909}}");

	json::value nested_list = json::parse("{\"startingFrame\":0,\"frames\":[{\"sprite\":\"357240685689300\",\"duration\":1.000000},{\"sprite\":\"546944778349700\",\"duration\":1.000000},{\"sprite\":\"546944777937600\",\"duration\":1.000000}]}");

	cout << "Premi un tasto per continuare...";
	return getchar();
}