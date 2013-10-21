#include <ControlModel.h>
#include <Sensor.h>

namespace CoreTests
{
    class ControlModelTests : public testing::Test
    {
    };

    TEST(ControlModelTests, testControlModel)
    {
        Core::Sensor sensor(Core::TEMPERATURE_SENSOR, 0, 50, 2);
        Core::ControlModel model(sensor, 5);
        model.update();

        Core::SensorMemory &sensorMemory = model.getSensorMemory();
        sensorMemory.addLayer(2);
        ASSERT_EQ(10, model.getSensorMemory().getGranules(1)[0].upperBound);
    }
} // namespace CoreTests