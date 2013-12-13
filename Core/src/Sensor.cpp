#include "Sensor.h"

#include <cstdlib>
#include <ctime>

namespace Core 
{
    Sensor::Sensor(SensorType type, double lowerBound, double upperBound, double measurementError) :
        type(type),
        lowerBound(lowerBound),
        upperBound(upperBound),
        measurementError(measurementError)
    {
        this->update();
        // initial value (stub)
        value = (upperBound - lowerBound) / 2;
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
        int shift = (rand() % 100) > 60 ? -2 : 2;
        value += shift;
    }
} // namespace Core
