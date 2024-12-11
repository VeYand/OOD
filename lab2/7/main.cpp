#include "WeatherStation/CWeatherData.h"
#include "WeatherStation/CFishermanDisplay.h"
#include "Animal/CDoggyObserver.h"
#include "Animal/CCattishObserver.h"
#include "Animal/CAnimalData.h"

void WorkWithAnimals()
{
	CAnimalData animalData;

	CCattishObserver catObserver;
	CDoggyObserver dogObserver;

	animalData.RegisterObserver(1, catObserver, AnimalEventType::AnimalAction);
	animalData.RegisterObserver(2, dogObserver, AnimalEventType::AnimalAction);

	animalData.SetAnimalAction(Animal::Cat, "chasing the mouse");
	animalData.SetAnimalAction(Animal::Dog, "barking at the cat");
}

void WorkWithFisherman()
{
	CWeatherData wd;

	CFishermanDisplay display;
	wd.RegisterObserver(5, display, WeatherEventType::Temperature);

	wd.SetMeasurements(25, 0.4, 760, {10, 10});

	wd.SetMeasurements(10, 0.8, 761, {10, 10});
}

int main()
{
	WorkWithAnimals();
	WorkWithFisherman();

	return 0;
}
