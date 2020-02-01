/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <algorithm>
#include <regex>
#include <sstream>
#include <vector>
#include "value.h"

namespace json
{
	class Deserializer final
	{
	public:

		static value parse(const std::string& source)
		{
			if (is_null(source)) return value();
			else if (is_bool(source)) return value(parse_bool(source));
			else if (is_number(source)) return value(parse_number(source));
			else if (is_array(source)) return value(parse_array(source));
			else if (is_object(source)) return value(parse_object(source));
			return value(parse_string(source));
		}

	private:

		Deserializer() = default;
		~Deserializer() = default;

		static bool parse_bool(const std::string& source)
		{
			static const std::string pattern{ "true" };

			return to_lower(source).find(pattern) != std::string::npos;
		}

		static number parse_number(const std::string& source)
		{
			return number(std::stod(source));
		}

		static std::string parse_string(const std::string& source)
		{
			return trim(trim(source, space), quote);
		}
		 
		static value::array_t parse_array(const std::string& source)
		{
			const std::string& src{ ltrim(rtrim(trim(source, space), rsquareb), lsquareb) };
			value::array_t array;
			for (const std::string& token : split(src, comma))
			{
				array.push_back(parse(token));
			}
			return array;
		}

		static value::object_t parse_object(const std::string& source)
		{
			const std::string& src{ ltrim(rtrim(trim(source, space), rgraphb), lgraphb) };
			value::object_t object;
			for (const std::string& line : split(src, comma))
			{
				const std::vector<std::string>& parts = split(line, equals);
				if (parts.size() == 2)
				{
					object.insert({ 
						parse_string(parts[0]),
						parse(parts[1]) 
						});
				}
			}
			return object;
		}

		static bool is_array(const std::string& source)
		{
			static const std::regex pattern{ "^\\s*\\[(.|\\n)*\\]\\s*$" };

			return std::regex_match(source, pattern);
		}

		static bool is_bool(const std::string& source)
		{
			static const std::regex true_pattern{ "^\\s*(T|t)(R|r)(U|u)(E|e)\\s*$" };
			static const std::regex false_pattern{ "^\\s*(F|f)(A|a)(L|l)(S|s)(E|e)\\s*$" };
			
			return std::regex_match(source, true_pattern)
				|| std::regex_match(source, false_pattern);
		}

		static bool is_null(const std::string& source)
		{
			static const std::regex pattern{ "^\\s*(N|n)(U|u)(L|l)(L|l)\\s*$" };

			return std::regex_match(source, pattern);
		}

		static bool is_number(const std::string& source)
		{
			static const std::regex pattern{ "^\\s*[+-]?\\d*\\.\\d+$|^\\s*[+-]?\\d+(\\.\\d*)?\\s*$" };

			return std::regex_match(source, pattern);
		}

		static bool is_object(const std::string& source)
		{
			static const std::regex pattern{ "^\\s*\\{(.|\\n)*\\}\\s*$" };

			return std::regex_match(source, pattern);
		}

		static bool is_string(const std::string& source)
		{
			// regex: starts with " and ends with ", whitespaces included
			static const std::regex pattern{ "^\\s*\".*\"\\s*$" };

			return std::regex_match(source, pattern);
		}
		
		static std::vector<std::string> split(const std::string& str, const char delimiter)
		{
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(str);
			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
			return tokens;
		}

		static std::string to_lower(const std::string& str)
		{
			std::string result(str);
			std::transform(result.begin(), result.end(), result.begin(), ::tolower);
			return result;
		}

		static std::string ltrim(const std::string& str, const char character)
		{
			std::string result(str);
			auto it2 = std::find_if(
				result.begin(),
				result.end(),
				[character](char ch)
				{ return ch != character; }
			);
			result.erase(result.begin(), it2);
			return result;
		}

		static std::string rtrim(const std::string& str, const char character)
		{
			std::string result(str);
			auto it1 = std::find_if(
				result.rbegin(),
				result.rend(),
				[character](char ch)
				{ return ch != character; }
			);
			result.erase(it1.base(), result.end());
			return result;
		}

		static std::string trim(const std::string& str, const char character)
		{
			return ltrim(rtrim(str, character), character);
		}

		static constexpr char comma = ',';
		static constexpr char endline = '\n';
		static constexpr char equals = ':';
		static constexpr char lsquareb = '[';
		static constexpr char lgraphb = '{';
		static constexpr char rsquareb = ']';
		static constexpr char rgraphb = '}';
		static constexpr char space = ' ';
		static constexpr char quote = '"';
		static constexpr char* quote_equals = "\":";
		static constexpr char tab = '\t';
	};

	value parse(const std::string& source){	return Deserializer::parse(source); }
}