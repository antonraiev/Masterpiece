#include "Sensor.h"

#include <cstdlib>
#include <ctime>

namespace Arduino 
{
    Sensor::Sensor(SensorType type) :
        type(type)
    {
        this->update();
        // initial value (stub)
        value = 25;
    }

    double Sensor::getLowerBound() const
    {
        return lowerBound;
    }

    double Sensor::getValue() const
    {
        return value;
    }

    double Sensor::getUpperBound() const
    {
        return upperBound;
    }

    SensorType Sensor::getType() const
    {
        return type;
    }

    double Sensor::getMeasurementError() const
    {
        return measurementError;
    }

    void Sensor::update()
    {
        // stub for now
        srand(time(NULL));
        int sign = (rand() % 100) > 80 ? -1 : 1;
        value += sign * (static_cast<double>(rand() % 4) / 10.f);
    }
} // namespace Core
