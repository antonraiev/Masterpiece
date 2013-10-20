#include "ControlModel.h"

namespace Core 
{
    ControlModel::ControlModel(Sensor sensor) :
        sensor(sensor),
        sensorMemory(sensor.getLowerBound(), sensor.getUpperBound(), 5)
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
