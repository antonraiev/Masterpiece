#include <Sensor.h>

namespace CoreTests
{
    class SensorTests : public testing::Test
    {
    };

    TEST(SensorTests, testUpdate)
    {
        Core::Sensor sensor(Core::TEMPERATURE_SENSOR, 0, 50, 0.5);
        double prevValue = sensor.getValue();
        for(size_t i = 0; i < 100; ++i) {
            sensor.update();
            double newValue = sensor.getValue();
//            ASSERT_EQ(newValue, prevValue);
            ASSERT_NEAR(prevValue, newValue, 0.35);
            prevValue = newValue;
        }
    }
} // namespace CoreTests