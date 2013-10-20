#include "ControlModel.h"

namespace Core 
{
    ControlModel::ControlModel(Sensor sensor, double granuleSize) :
        sensor(sensor),
        sensorMemory(sensor.getLowerBound(), sensor.getUpperBound(), granuleSize)
    {
    }

    const Sensor& ControlModel::getSensor() const
    {
        return sensor;
    }

    const SensorMemory& ControlModel::getSensorMemory() const
    {
        return sensorMemory;
    }

    void ControlModel::update()
    {
        sensor.update();
        sensorMemory.update(sensor.getValue());
    }
} // namespace Core
