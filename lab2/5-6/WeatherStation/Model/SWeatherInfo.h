#ifndef SWEATHERINFO_H
#define SWEATHERINFO_H
#include "SWindInfo.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    SWindInfo wind{};
};

#endif //SWEATHERINFO_H