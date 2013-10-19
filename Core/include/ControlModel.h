#ifndef CONTROLMODEL_H
#define CONTROLMODEL_H

#include "SensorMemory.h"
#include "Sensor.h"

namespace Core 
{
    /** 
    * General control class
    * Represents the control model of one sensor
    * A kind of GOF Mediator pattern (idea, but not implementation)
    */
    class ControlModel
    {
    public:
        /** 
        * Create new ControlModel for a specified sensor
        * @param sensor The sensor which the model will use
	    */
        explicit ControlModel(Sensor sensor);

        /** 
        * Get the sensor used by the model
        * @returns The sensor used by the model
	    */
        Sensor getSensor() const;

        /** 
        * Get the sensor memory
        * @returns The sensor memory 
        */
        SensorMemory getSensorMemory() const;

        /** 
        * Update all model data (The value from sensor, the sensor memory and so on)
        */
        void update();

    private:
        Sensor sensor;
        SensorMemory sensorMemory;
    };
} // namespace Core

#endif /* CONTROLMODEL_H */
