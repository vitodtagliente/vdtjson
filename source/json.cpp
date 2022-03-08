#include <vdtjson/json.h>

namespace json
{
	value array() { return value{ value::array_t{} }; }
	value array(const value::array_t& data) { return value(data); }
	value object() { return value{ value::object_t{} }; }
	value object(const value::object_t& data) { return value(data); }

	value parse(const std::string& source) 
	{ 
		return Deserializer::parse(source); 
	}

	std::string to_string(const value& value) 
	{ 
		return Serializer::to_string(value); 
	}
}