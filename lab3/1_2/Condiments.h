#pragma once

#include "IBeverage.h"

// Базовый декоратор "Добавка к напитку". Также является напитком
class CCondimentDecorator : public IBeverage
{
public:
	[[nodiscard]] std::string GetDescription() const override
	{
		// Описание декорированного напитка добавляется к описанию оборачиваемого напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	[[nodiscard]] double GetCost() const override
	{
		// Стоимость складывается из стоимости добавки и стоимости декорируемого напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

	// Стоимость и описание добавки вычисляется в классах конкретных декораторов
	[[nodiscard]] virtual std::string GetCondimentDescription() const = 0;

	[[nodiscard]] virtual double GetCondimentCost() const = 0;

protected:
	explicit CCondimentDecorator(IBeveragePtr &&beverage)
		: m_beverage(move(beverage))
	{
	}

private:
	IBeveragePtr m_beverage;
};

// Добавка из корицы
class CCinnamon final : public CCondimentDecorator
{
public:
	explicit CCinnamon(IBeveragePtr &&beverage)
		: CCondimentDecorator(move(beverage))
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 20;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Cinnamon";
	}
};

// Лимонная добавка
class CLemon final : public CCondimentDecorator
{
public:
	explicit CLemon(IBeveragePtr &&beverage, unsigned quantity = 1)
		: CCondimentDecorator(move(beverage))
		  , m_quantity(quantity)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 10.0 * m_quantity;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};


enum class IceCubeType
{
	DRY, // Сухой лед (для суровых сибирских мужиков)
	WATER // Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет на стоимость
// и описание
class CIceCubes final : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr &&beverage, const unsigned quantity, const IceCubeType type = IceCubeType::WATER)
		: CCondimentDecorator(move(beverage))
		  , m_quantity(quantity)
		  , m_type(type)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		// Чем больше кубиков, тем больше стоимость.
		// Сухой лед стоит дороже
		return (m_type == IceCubeType::DRY ? 10 : 5) * m_quantity;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::DRY ? "Dry" : "Water")
		       + " ice cubes x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

// Тип сиропа
enum class SyrupType
{
	CHOCOLATE, // Шоколадный
	MAPLE, // Кленовый
};

// Добавка "Сироп"
class CSyrup final : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr &&beverage, SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		  , m_syrupType(syrupType)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 15;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::CHOCOLATE ? "Chocolate" : "Maple")
		       + " syrup";
	}

private:
	SyrupType m_syrupType;
};

// Шоколадная крошка
class CChocolateCrumbs final : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr &&beverage, const unsigned mass)
		: CCondimentDecorator(move(beverage))
		  , m_mass(mass)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 2.0 * m_mass;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

// Кокосовая стружка
class CCoconutFlakes final : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr &&beverage, const unsigned mass)
		: CCondimentDecorator(move(beverage))
		  , m_mass(mass)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 1.0 * m_mass;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

class CCream final : public CCondimentDecorator
{
public:
	explicit CCream(IBeveragePtr &&beverage)
		: CCondimentDecorator(move(beverage))
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 25;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Cream";
	}
};

class CChocolate final : public CCondimentDecorator
{
public:
	explicit CChocolate(IBeveragePtr &&beverage, const unsigned slices)
		: CCondimentDecorator(move(beverage))
	{
		if (slices > MAX_SLICES)
		{
			throw std::invalid_argument("Invalid slices count. Max slices: " + std::to_string(MAX_SLICES));
		}

		m_slices = slices;
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return m_slices * SLICE_COST;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::to_string(m_slices) + " chocolate slices";
	}

private:
	const unsigned SLICE_COST = 10;
	const unsigned MAX_SLICES = 5;

	unsigned m_slices;
};

enum class LiquorType
{
	CHOCOLATE,
	NUTTY
};

inline std::string convertLiquorTypeToString(const LiquorType liqueurType)
{
	switch (liqueurType)
	{
		case LiquorType::CHOCOLATE: return "Chocolate";
		case LiquorType::NUTTY: return "Nutty";
		default: return "Unknown LiquorType";
	}
}

class CLiquor final : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr &&beverage, const LiquorType type)
		: CCondimentDecorator(std::move(beverage)), m_type(type)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 50;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return convertLiquorTypeToString(m_type) + " Liquor";
	}

private:
	LiquorType m_type;
};
