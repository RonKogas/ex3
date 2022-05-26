#ifndef HEALTHPOINTS_LIBRARY_H
#define HEALTHPOINTS_LIBRARY_H

#include <iostream>

const int DEFAULT_MAX_HEALTH_POINTS = 100;

class HealthPoints {
public:
    /**
     * C'tor of HealthPoints class.
     *
     * @param maxHealthPoints - maximum number of health points.
     * @return
     *      A new instance of HealthPoints.
    */
    HealthPoints(const int maxHealthPoints = DEFAULT_MAX_HEALTH_POINTS);

    /**
     * using the default copy C'tor, D'tor and assignment operator.
    */
    HealthPoints(const HealthPoints&) = default;
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints& healthPoints) = default;

    HealthPoints& operator+=(const int pointsToAdd);
    HealthPoints& operator-=(const int pointsToRemove);
    class InvalidArgument {};

private:
    int m_maxHealthPoints;
    int m_healthPoints;

    friend bool operator<(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);
    friend std::ostream& operator<<(std::ostream& out, const HealthPoints&);
};

HealthPoints operator+(const HealthPoints& healthPoints, const int pointsToAdd);
HealthPoints operator+(const int pointsToAdd, const HealthPoints& healthPoints);
HealthPoints operator-(const HealthPoints& healthPoints, const int pointsToRemove);
bool operator==(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);
bool operator!=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);
bool operator>=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);
bool operator>(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);
bool operator<=(const HealthPoints& healthPointsA, const HealthPoints& healthPointsB);

#endif //HEALTHPOINTS_LIBRARY_H
