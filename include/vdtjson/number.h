/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

namespace json
{
	class number
	{
	public:

		enum class Type : uint8_t
		{
			Int		= 0,
			Float	= 1,
			Double	= 2
		};

		using value_t = double;

		number()
			: m_type(Type::Int)
			, m_value(0)
		{}

		number(const int value)
			: m_type(Type::Int)
			, m_value(value)
		{}

		number(const float value)
			: m_type(Type::Float)
			, m_value(value)
		{}

		number(const double value)
			: m_type(Type::Double)
			, m_value(value)
		{}

		bool is_int() const { return m_type == Type::Int; }
		bool is_float() const { return m_type == Type::Float; }
		bool is_double() const { return m_type == Type::Double; }

		int as_int() const { return static_cast<int>(m_value); }
		float as_float() const { return static_cast<float>(m_value); }
		double as_double() const { return m_value; }

		Type type() const { return m_type; }

		bool operator== (const number& other) const
		{
			return m_type == other.m_type
				&& m_value == other.m_value;
		}

		bool operator!= (const number& other) const
		{
			return m_type != other.m_type
				|| m_value != other.m_value;
		}

		number& operator= (const int value)
		{
			m_type = Type::Int;
			m_value = value;
			return *this;
		}

		number& operator= (const float value)
		{
			m_type = Type::Float;
			m_value = value;
			return *this;
		}

		number& operator= (const double value)
		{
			m_type = Type::Double;
			m_value = value;
			return *this;
		}

		// Prefix increment operator
		number& operator++ () { m_value++; return *this; }
		// Postfix increment operator
		number operator++ (int)
		{
			number temp(m_type, m_value);
			++(*this);
			return temp;
		}
		// Prefix decrement operator
		number& operator-- () { m_value--; return *this; }
		// Postfix decrement operator
		number operator-- (int)
		{
			number temp(m_type, m_value);
			--(*this);
			return temp;
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number& operator += (const T value) 
		{ 
			m_value += static_cast<double>(value); 
			return *this; 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number& operator -= (const T value) 
		{ 
			m_value -= static_cast<double>(value); 
			return *this; 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number& operator *= (const T value) 
		{
			m_value *= static_cast<double>(value); 
			return *this; 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number& operator /= (const T value) 
		{ 
			m_value /= static_cast<double>(value); 
			return *this; 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number operator+ (const T value) const 
		{ 
			return number(m_type, m_value + static_cast<double>(value)); 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number operator- (const T value) const 
		{ 
			return number(m_type, m_value - static_cast<double>(value)); 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number operator* (const T value) const 
		{ 
			return number(m_type, m_value * static_cast<double>(value)); 
		}

		template<typename T, typename TEnable = std::enable_if_t<std::is_arithmetic<T>::value>>
		number operator/ (const T value) const 
		{ 
			return number(m_type, m_value / static_cast<double>(value)); 
		}

	private:

		number(const Type type, const double value)
			: m_type(type)
			, m_value(value)
		{}
		
		Type m_type;
		value_t m_value;
	};
}