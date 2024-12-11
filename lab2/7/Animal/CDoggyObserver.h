#ifndef CCANINEOBSERVER_H
#define CCANINEOBSERVER_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "CAnimalData.h"
#include "Model/SAnimalInfo.h"

class CDoggyObserver final : public IObserver<SAnimalInfo, AnimalEventType>
{
public:
	void Update(SAnimalInfo const &data, const AnimalEventType eventType) override
	{
		if (eventType == AnimalEventType::AnimalAction && data.animal == Animal::Dog)
		{
			std::cout << "The dog is now " << data.action << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}
};

#endif //CCANINEOBSERVER_H
