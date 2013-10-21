#include "ControlModel.h"

namespace Core 
{
    ControlModel::ControlModel(Sensor sensor, double granuleSize) :
        sensor(sensor),
        sensorMemory(sensor.getLowerBound(), sensor.getUpperBound(), granuleSize)
    {
    }

    Sensor& ControlModel::getSensor()
    {
        return sensor;
    }

    SensorMemory& ControlModel::getSensorMemory()
    {
        return sensorMemory;
    }

    void ControlModel::update()
    {
        sensor.update();
        sensorMemory.update(sensor.getValue());
    }
} // namespace Core
