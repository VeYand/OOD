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
	Dry, // Сухой лед (для суровых сибирских мужиков)
	Water // Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет на стоимость
// и описание
class CIceCubes final : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr &&beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
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
		return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
		       + " ice cubes x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

// Тип сиропа
enum class SyrupType
{
	Chocolate, // Шоколадный
	Maple, // Кленовый
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
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
		       + " syrup";
	}

private:
	SyrupType m_syrupType;
};

// Шоколадная крошка
class CChocolateCrumbs final : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr &&beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		  , m_mass(mass)
	{
	}

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
	CCoconutFlakes(IBeveragePtr &&beverage, unsigned mass)
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
