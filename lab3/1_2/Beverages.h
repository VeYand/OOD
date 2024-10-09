#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	explicit CBeverage(std::string description)
		: m_description(std::move(description))
	{
	}

	[[nodiscard]] std::string GetDescription() const final
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	explicit CCoffee(const std::string &description = "Coffee")
		: CBeverage(description)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino final : public CCoffee
{
public:
	explicit CCappuccino(bool isDoublePortion = false)
		: CCoffee(isDoublePortion ? "Double Cappuccino" : "Standard Cappuccino"),
		  m_isDoublePortion(isDoublePortion)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return m_isDoublePortion
			       ? 120
			       : 80;
	}

private:
	bool m_isDoublePortion;
};

// Латте
class CLatte final : public CCoffee
{
public:
	explicit CLatte(const bool isDoublePortion = false)
		: CCoffee(isDoublePortion ? "Double Latte" : "Standard Latte"),
		  m_isDoublePortion(isDoublePortion)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return m_isDoublePortion
			       ? 130
			       : 90;
	}

private:
	bool m_isDoublePortion;
};

enum class TeaType
{
	BLACK = 1,
	OOLONG,
	WHITE,
	YELLOW,
};

inline std::string convertTeaTypeToString(const TeaType teaType)
{
	switch (teaType)
	{
		case TeaType::BLACK: return "Black";
		case TeaType::OOLONG: return "Oolong";
		case TeaType::WHITE: return "White";
		case TeaType::YELLOW: return "Yellow";
		default: return "Unknown TeaType";
	}
}

// Чай
class CTea final : public CBeverage
{
public:
	explicit CTea(const TeaType teaType)
		: CBeverage(convertTeaTypeToString(teaType) + " Tea")
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return 30;
	}
};

enum class MilkshakeSize
{
	SMALL = 1,
	MEDIUM,
	LARGE,
};

// Иимена функция с заглавной
inline std::string convertMilkshakeSizeTypeToString(const MilkshakeSize sizeType)
{
	switch (sizeType)
	{
		case MilkshakeSize::SMALL: return "Small";
		case MilkshakeSize::MEDIUM: return "Medium";
		case MilkshakeSize::LARGE: return "Large";
		default: return "Unknown MilkshakeSizeType";
	}
}


// Молочный коктейль
class CMilkshake final : public CBeverage
{
public:
	explicit CMilkshake(const MilkshakeSize sizeType)
		: CBeverage(convertMilkshakeSizeTypeToString(sizeType) + " Milkshake"),
		  m_size(sizeType)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		switch (m_size)
		{
			case MilkshakeSize::SMALL: return 50;
			case MilkshakeSize::MEDIUM: return 60;
			case MilkshakeSize::LARGE: return 80;
		}

		return 0;
	}

private:
	MilkshakeSize m_size;
};
