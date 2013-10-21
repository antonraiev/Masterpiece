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
            Core::SensorType nativeType = static_cast<Core::SensorType>(type);
            sensor = new Core::Sensor(nativeType, lowerBound, upperBound,
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
        Sensor(Core::Sensor &nativeSensor)
        {
            sensor = &nativeSensor;
        }

        property const Core::Sensor& Native
        {
            const Core::Sensor& get()
            {
                return *sensor;
            }
        }

    private:
        Core::Sensor *sensor;
    };
} // namespace CoreWrapper