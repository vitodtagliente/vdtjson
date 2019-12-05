/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include "value.h"

namespace json
{
	std::string to_string(const value&);
	std::string to_string(const number&);
	std::string to_string(const value::array_t&);
	std::string to_string(const value::object_t&);

	std::string to_string(const value& value)
	{
		static constexpr char* quote = "\"";

		switch (value.type())
		{
		case value::Type::Bool:
			return std::to_string(value.as_bool());
		case value::Type::Number:
			return to_string(value.as_number());
		case value::Type::Array:
			return to_string(value.as_array());
		case value::Type::Object:
			return to_string(value.as_object());
		case value::Type::String:
		default:
			return std::string{quote}.append(value.as_string()).append(quote);
		}
	}

	std::string to_string(const number& number)
	{
		switch (number.type())
		{
		case number::Type::Int:
			return std::to_string(number.as_int());
		case number::Type::Float:
			return std::to_string(number.as_float());
		case number::Type::Double:
		default:
			return std::to_string(number.as_double());
		}
	}

	std::string to_string(const value::array_t& array)
	{
		static constexpr char* comma = ",";

		std::string result{ "[" };

		const size_t size = array.size();
		for (int i = 0; i < size; ++i)
		{
			result.append(to_string(array[i]));
			if (i < size - 1) result.append(comma);
		}

		result.append("]");
		return result;
	}

	std::string to_string(const value::object_t& object)
	{
		static constexpr char* comma = ",";
		static constexpr char* quote = "\"";
		static constexpr char* equals = "\":";

		std::string next{};

		std::string result{ "{" };

		for (const auto& pair : object)
		{
			result.append(next)
				.append(quote)
				.append(pair.first)
				.append(equals)
				.append(to_string(pair.second));
			next = comma;
		}

		return result.append("}");
	}
}