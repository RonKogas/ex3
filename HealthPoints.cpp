#include "HealthPoints.h"

using std::ostream;

HealthPoints::HealthPoints(const int maxHealthPoints)
{
    if (maxHealthPoints <= 0) {
        throw InvalidArgument();
    }
    m_maxHealthPoints = maxHealthPoints;
    m_healthPoints = maxHealthPoints;
}

HealthPoints& HealthPoints::operator+=(const int pointsToAdd)
{
    if (m_healthPoints + pointsToAdd > m_maxHealthPoints) {
        m_healthPoints = m_maxHealthPoints;
    } else if (m_healthPoints + pointsToAdd < 0) {
        m_healthPoints = 0;
    } else {
        m_healthPoints += pointsToAdd;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int pointsToRemove)
{
    return *this += (-pointsToRemove);
}

HealthPoints operator+(const HealthPoints& healthPoints, const int pointsToAdd)
{
    HealthPoints result = healthPoints;
    return result += pointsToAdd;
}

HealthPoints operator+(const int pointsToAdd, const HealthPoints& healthPoints)
{
    return healthPoints + pointsToAdd;
}

HealthPoints operator-(const HealthPoints& healthPoints, const int pointsToRemove)
{
    return healthPoints + (-pointsToRemove);
}

bool operator<(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return healthPointsA.m_healthPoints < healthPointsB.m_healthPoints;
}

bool operator<=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return !(healthPointsB < healthPointsA);
}

bool operator>(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return healthPointsB < healthPointsA;
}

bool operator>=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return healthPointsB <= healthPointsA;
}

bool operator==(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return (healthPointsA <= healthPointsB) && (healthPointsB <= healthPointsA);
}

bool operator!=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB)
{
    return !(healthPointsA == healthPointsB);
}

ostream& operator<<(ostream& out, const HealthPoints& healthPoints)
{
    return out << healthPoints.m_healthPoints << "(" << healthPoints.m_maxHealthPoints << ")";
}