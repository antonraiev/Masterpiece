#ifndef SENSORTYPE_H
#define SENSORTYPE_H

namespace Arduino
{
    enum class SensorType {TEMPERATURE_SENSOR, HUMIDITY_SENSOR,
        ULTRASONIC_SENSOR = 'u'};
}

#endif