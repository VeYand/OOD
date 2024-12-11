#ifndef CANIMALDATA_H
#define CANIMALDATA_H

#include "../Observable/CObservable.h"
#include "Model/SAnimalInfo.h"

enum class AnimalEventType
{
	AnimalAction,
};

class CAnimalData final : public CObservable<SAnimalInfo, AnimalEventType>
{
public:
	void SetAnimalAction(const Animal animal, const std::string &action)
	{
		m_info.animal = animal;
		m_info.action = action;

		NotifyObservers(AnimalEventType::AnimalAction);
	}

protected:
	[[nodiscard]] SAnimalInfo GetChangedData() const override
	{
		return m_info;
	}

private:
	SAnimalInfo m_info{};
};

#endif //CANIMALDATA_H
