#include "ControlModel.h"

namespace Core 
{
    ControlModel::ControlModel(Sensor sensor) :
        sensor(sensor),
       sensorMemory(sensor.getLowerBound(), sensor.getUpperBound(), 5)
    {
    }

    Sensor ControlModel::getSensor() const
    {
    }

    SensorMemory ControlModel::getSensorMemory() const
    {
    }

    void ControlModel::update()
    {
    }
} // namespace Core
