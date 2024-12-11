#ifndef CFELINEOBSERVER_H
#define CFELINEOBSERVER_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "Model/SAnimalInfo.h"

class CCattishObserver final : public IObserver<SAnimalInfo, AnimalEventType>
{
public:
	void Update(SAnimalInfo const &data, const AnimalEventType eventType) override
	{
		if (eventType == AnimalEventType::AnimalAction && data.animal == Animal::Cat)
		{
			std::cout << "The cat is now " << data.action << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}
};

#endif //CFELINEOBSERVER_H
