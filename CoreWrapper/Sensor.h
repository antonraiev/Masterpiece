#include <Sensor.h>

namespace CoreWrapper
{
    public enum class SensorType {TEMPERATURE_SENSOR, HUMIDITY_SENSOR, DISTANCE_SENSOR};

    public ref class Sensor
    {
    public:

        Sensor(SensorType type, double lowerBound, double upperBound,
            double measurementError)
        {
            Arduino::SensorType nativeType = static_cast<Arduino::SensorType>(type);
            sensor = new Arduino::Sensor(nativeType, lowerBound, upperBound,
                measurementError);
        }

        ~Sensor()
        {
            delete sensor;
        }

        property double LowerBound
        {
            double get()
            {
                return sensor->getLowerBound();
            }
        }

        property double Value
        {
            double get()
            {
                return sensor->getValue();
            }
        }

        property double UpperBound
        {
            double get()
            {
                return sensor->getUpperBound();
            }
        }

        property SensorType Type
        {
            SensorType get()
            {
                SensorType type = static_cast<SensorType>(sensor->getType());
                return type;
            }
        }

        property double MeasurementError
        {
            double get()
            {
                return sensor->getMeasurementError();
            }
        }

        void Update()
        {
            sensor->update();
        }

    internal:
        Sensor(Arduino::Sensor &nativeSensor)
        {
            sensor = &nativeSensor;
        }

        property const Arduino::Sensor& Native
        {
            const Arduino::Sensor& get()
            {
                return *sensor;
            }
        }

    private:
        Arduino::Sensor *sensor;
    };
} // namespace CoreWrapper