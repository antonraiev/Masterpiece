#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "SensorType.h"

namespace Arduino
{
    /**
    * Represents the sensor connected to the Arduino robot
    */
    class Sensor
    {
    public:
        /**
         * Create new sensor
         * @param type Sensor type e.g. HUMIDITY_SENSOR
         */
        explicit Sensor(SensorType type);

        /**
        * Get the lower bound of the sensor's value
        * @returns The lower bound of the sensor's value
        */
        double getLowerBound() const;

        /**
        * Get the last measured value from the sensor
        * @returns The last measured value from the sensor
        */
        double getValue() const;

        /**
        * Get the upper bound of the sensor's value
        * @returns The upper bound of the sensor's value
        */
        double getUpperBound() const;

        /**
        * Get the type of the sensor
        * @returns Type of the sensor e.g. HUMIDITY_SENSOR
        */
        SensorType getType() const;

        /**
        * Get the measurement error of the sensor
        * @returns The measurement error of the sensor
        */
        double getMeasurementError() const;

        /**
        * Get the recent value from the sensor
        */
        void update();

    private:
        double value;
        SensorType type;
        double lowerBound;
        double upperBound;
        double measurementError;
    };
} // namespace Core

#endif /* SENSOR_H */
