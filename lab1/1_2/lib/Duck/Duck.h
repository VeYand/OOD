#ifndef DUCK_H
#define DUCK_H

#include "Dance/IDanceBehavior.h"
#include "Fly/IFlyBehavior.h"
#include "Quack/IQuackBehavior.h"
#include "QuackPolicy/IQuackPolicy.h"

#include <cassert>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior,
		std::unique_ptr<IQuackPolicy>&& quackPolicy
		)
		: m_quackBehavior(std::move(quackBehavior)),
		  m_danceBehavior(std::move(danceBehavior)),
		  m_quackPolicy(std::move(quackPolicy))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		assert(m_quackPolicy);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack() const
	{
		m_quackBehavior->Quack();
	}

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly() const
	{
		HandleFlightWithQuack();
	}

	void Dance() const
	{
		m_danceBehavior->Dance();
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
	std::unique_ptr<IQuackPolicy> m_quackPolicy;

	void HandleFlightWithQuack() const
	{
		const auto flightCount = m_flyBehavior->GetFlightCount();
		const auto nextFlightCount = m_flyBehavior->GetNextFlightCount();
		const auto canFly = flightCount != nextFlightCount;

		if (canFly && m_quackPolicy->ShouldQuack(nextFlightCount, false))
		{
			m_quackBehavior->Quack();
		}

		m_flyBehavior->Fly();

		if (canFly && m_quackPolicy->ShouldQuack(nextFlightCount, true))
		{
			m_quackBehavior->Quack();
		}
	}
};

#endif // DUCK_H