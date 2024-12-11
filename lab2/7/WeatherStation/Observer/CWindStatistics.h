#ifndef CWINDSTATISTICS_H
#define CWINDSTATISTICS_H

#include <cmath>

class CWindStatistics
{
public:
    void AddValue(const SWindInfo wind)
    {
        if (m_minSpeed > wind.speed)
        {
            m_minSpeed = wind.speed;
        }
        if (m_maxSpeed < wind.speed)
        {
            m_maxSpeed = wind.speed;
        }
        m_totalSpeed += wind.speed;

        const double radianDirection = wind.direction * M_PI / 180.0;

        const double x = wind.speed * cos(radianDirection);
        const double y = wind.speed * sin(radianDirection);

        m_sumX += x;
        m_sumY += y;
        ++m_count;
    }

    [[nodiscard]] double GetMaxSpeed() const
    {
        return m_maxSpeed;
    }

    [[nodiscard]] double GetMinSpeed() const
    {
        return m_minSpeed;
    }

    [[nodiscard]] double GetAverageSpeed() const
    {
        if (m_count == 0)
        {
            return 0;
        }

        return m_totalSpeed / m_count;
    }

    [[nodiscard]] double GetAverageDirection() const
    {
        if (m_count == 0)
        {
            return 0;
        }

        const double averageDirection = atan2(m_sumY / m_count, m_sumX / m_count) * 180.0 / M_PI;
        return fmod(averageDirection + 360.0, 360.0);
    }

private:
    double m_totalSpeed = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();
    double m_sumX = 0;
    double m_sumY = 0;
    unsigned m_count = 0;
};

#endif //CWINDSTATISTICS_H
