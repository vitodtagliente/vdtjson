/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include "value.h"

namespace json
{
	class Serializer final
	{
	public:

		static std::string to_string(const value& value)
		{
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
				return std::string{ quote }.append(value.as_string()).append(quote);
			}
		}

		static std::string to_string(const number& number)
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

		static std::string to_string(const value::array_t& array)
		{
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

		static std::string to_string(const value::object_t& object)
		{

			std::string next{};

			std::string result{ "{" };

			for (const auto& pair : object)
			{
				result.append(next)
					.append(quote)
					.append(pair.first)
					.append(quote_equals)
					.append(to_string(pair.second));
				next = comma;
			}

			return result.append("}");
		}


	private:

		Serializer() = default;
		~Serializer() = default;

		static constexpr char* comma = ",";
		static constexpr char* equals = ":";
		static constexpr char* quote = "\"";
		static constexpr char* quote_equals = "\":";
	};

	std::string to_string(const value& value) { return Serializer::to_string(value); }
	std::string to_string(const number& value) { return Serializer::to_string(value); }
	std::string to_string(const value::array_t& value) { return Serializer::to_string(value); }
	std::string to_string(const value::object_t& value) { return Serializer::to_string(value); }
}