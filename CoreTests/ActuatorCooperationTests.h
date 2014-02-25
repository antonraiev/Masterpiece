#include <ActuatorCooperation.h>

namespace CoreTests
{
    class ActuatorCooperationTests : public testing::Test
    {
    };

    TEST(ActuatorCooperationTests, testSimple)
    {
        Core::ActuatorCooperation cooperation(0.1, 10, 2, 3, 4);
        cooperation.update(0.1);
        int result = cooperation.getControl();
        cooperation.update(0.1);
        result = cooperation.getControl();
        cooperation.update(0.1);
        result = cooperation.getControl();
    }
}
