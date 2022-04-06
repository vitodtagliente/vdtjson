/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <algorithm>
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
			std::string src{ trim(source, space) };
			src = src.substr(1, src.length() - 2);
			value::array_t array;

			size_t index = 0;
			std::string value;
			while (!src.empty() && (index = next_value(src, value)) != std::string::npos)
			{
				array.push_back(parse(value));
				src = src.substr(std::min(src.length(), index + 1));
			};

			return array;
		}

		static value::object_t parse_object(const std::string& source)
		{
			std::string src{ trim(source, space) };
			value::object_t object;

			size_t index = 0;
			std::string key, value;
			while ((index = next_key(src, key)) != std::string::npos)
			{
				src = src.substr(index + 2);
				index = next_value(src, value);
				if (index != std::string::npos)
				{
					object.insert({ key, parse(value) });
					src = src.substr(index + 1);
				}
				else
				{
					break;
				}
			};

			return object;
		}

		static bool is_array(const std::string& source)
		{
			const std::string src = trim(source, space);
			if (src.empty()) return false;
			return src.at(0) == lsquareb && src.at(src.length() - 1) == rsquareb;
		}

		static bool is_bool(const std::string& source)
		{
			const std::string src = to_lower(trim(source, space));
			return src == "true"
				|| src == "false";
		}

		static bool is_null(const std::string& source)
		{
			const std::string src = to_lower(trim(source, space));
			return src == "null";
		}

		static bool is_number(const std::string& source)
		{
			const std::string src = trim(source, space);
			return !src.empty() && src.find_first_not_of("-.0123456789") == std::string::npos;
		}

		static bool is_object(const std::string& source)
		{
			const std::string src = trim(source, space);
			if (src.empty()) return false;
			return src.at(0) == lgraphb && src.at(src.length() - 1) == rgraphb;
		}

		static bool is_string(const std::string& source)
		{
			const std::string src = trim(source, space);
			if (src.empty()) return false;
			return src.at(0) == quote && src.at(src.length() - 1) == quote;
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
			std::string result;
			std::transform(str.begin(), str.end(), std::back_inserter(result),
				[](const char c) -> char { return static_cast<char>(std::tolower(c)); }
			);
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

		static size_t next_closure(const std::string& text, const char left, const char right)
		{
			size_t n = 0;
			for (size_t i = 1; i < text.length(); ++i)
			{
				const char c = text.at(i);
				if (c == left)
				{
					++n;
				}
				else if (c == right)
				{
					if (n == 0)
					{
						return (i + 1);
					}
					--n;
				}
			}

			return std::string::npos;
		}

		static size_t until_next(const std::string& text, const std::vector<char>& characters)
		{
			for (size_t i = 0; i < text.length(); ++i)
			{
				if (std::find(characters.begin(), characters.end(), text.at(i)) != characters.end())
				{
					return i;
				}
			}
			return text.length();
		}

		static size_t next_key(const std::string& text, std::string& key)
		{
			key.clear();
			const size_t end = text.find(quote_equals);
			if (end != std::string::npos)
			{
				const size_t begin = text.find_last_of(quote, end - 1);
				if (begin != std::string::npos)
				{
					key = text.substr(begin + 1, end - 1 - begin);
				}
			}
			return end;
		}

		static size_t next_value(const std::string& text, std::string& value)
		{
			value.clear();

			if (text.empty())
			{
				return 0;
			}

			size_t pos = 0;
			if (text.at(0) == lgraphb)
			{
				pos = next_closure(text, lgraphb, rgraphb);
			}
			else if (text.at(0) == lsquareb)
			{
				pos = next_closure(text, lsquareb, rsquareb);
			}
			else
			{
				pos = until_next(text, { comma, rsquareb, rgraphb });
			}

			value = text.substr(0, pos);
			return pos;
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

	value parse(const std::string& source);
}