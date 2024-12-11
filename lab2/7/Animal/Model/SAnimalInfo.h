#ifndef SANIMALINFO_H
#define SANIMALINFO_H

#include <string>

enum class Animal
{
	Cat,
	Dog,
};

struct SAnimalInfo
{
	Animal animal;
	std::string action;
};

#endif //SANIMALINFO_H
