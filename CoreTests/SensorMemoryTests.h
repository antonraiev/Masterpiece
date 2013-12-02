#include <SensorMemory.h>

namespace CoreTests
{
    class SensorMemoryTests : public testing::Test
    {
    public:
        static void checkGranulesEqual(const Core::Granule &expected,
            const Core::Granule &produced)
        {
            ASSERT_EQ(expected.lowerBound, produced.lowerBound);
            ASSERT_EQ(expected.upperBound, produced.upperBound);
            ASSERT_EQ(expected.alpha, produced.alpha);
        }
    };

    TEST_F(SensorMemoryTests, testCreation)
    {
        using Core::Granule;
        Core::SensorMemory sensorMemory(0, 15, 3);
        ASSERT_EQ(1, sensorMemory.getLayerCount());
        std::vector<Granule> granules = sensorMemory.getGranules();
        Granule expectedGranules[] = 
        {
            Granule(0, 3, -1, 25),
            Granule(3, 6, -1, 25),
            Granule(6, 9, -1, 25),
            Granule(9, 12, -1, 25),
            Granule(12, 15, -1, 25),
        };

        for(size_t i = 0; i < granules.size(); ++i) {
            this->checkGranulesEqual(expectedGranules[i], granules[i]);
        }
    }

    TEST_F(SensorMemoryTests, testCreationFractional)
    {
        using Core::Granule;
        Core::SensorMemory sensorMemory(0, 7.5, 2.5);
        Granule expectedGranules[] = 
        {
            Granule(0, 2.5, -1, 25),
            Granule(2.5, 5, -1, 25),
            Granule(5, 7.5, -1, 25),
        };

        std::vector<Granule> granules = sensorMemory.getGranules();
        for(size_t i = 0; i < granules.size(); ++i) {
            this->checkGranulesEqual(expectedGranules[i], granules[i]);
        }
    }

    TEST_F(SensorMemoryTests, testAddLayer)
    {
        using Core::Granule;
        Core::SensorMemory sensorMemory(10, 28, 3);
        sensorMemory.addLayer(2);
        ASSERT_EQ(sensorMemory.getLayerCount(), 2);

        std::vector<Granule> granules = sensorMemory.getGranules(1);
        ASSERT_EQ(3, granules.size());
        Granule expectedGranules[] = 
        {
            Granule(10, 16, -1, 25),
            Granule(16, 22, -1, 25),
            Granule(22, 28, -1, 25),
        };

        for(size_t i = 0; i < granules.size(); ++i) {
            this->checkGranulesEqual(expectedGranules[i], granules[i]);
        }
    }

    TEST_F(SensorMemoryTests, testRemoveTopLayer)
    {
        Core::SensorMemory sensorMemory(5, 15, 1);
        ASSERT_THROW(sensorMemory.removeTopLayer(), std::runtime_error);

        sensorMemory.addLayer(2);
        sensorMemory.removeTopLayer();
        ASSERT_EQ(sensorMemory.getLayerCount(), 1);
        ASSERT_THROW(sensorMemory.removeTopLayer(), std::runtime_error);
    }

    TEST_F(SensorMemoryTests, testAddLayerOdd)
    {
        using Core::Granule;
        Core::SensorMemory sensorMemory(-10, 11, 3);
        sensorMemory.addLayer(3);
        Granule expectedGranules[] = 
        {
            Granule(-10, -1, -1, 25),
            Granule(-1, 8, -1, 25),
            Granule(8, 11, -1, 25),
        };

        std::vector<Granule> granules = sensorMemory.getGranules(1);
        for(size_t i = 0; i < granules.size(); ++i) {
            this->checkGranulesEqual(expectedGranules[i], granules[i]);
        }
    }

    TEST_F(SensorMemoryTests, testUpdate)
    {
        double eps = 0.001;
        Core::SensorMemory sensorMemory(0, 30, 10);
        sensorMemory.update(10);
        ASSERT_NEAR(-0.05, sensorMemory.getGranules()[0].alpha, eps);
        ASSERT_NEAR(0.05, sensorMemory.getGranules()[1].alpha, eps);
        ASSERT_NEAR(-0.95, sensorMemory.getGranules()[2].alpha, eps);

        sensorMemory.update(12.5);
        ASSERT_NEAR(-0.45, sensorMemory.getGranules()[0].alpha, eps);
        ASSERT_NEAR(0.45, sensorMemory.getGranules()[1].alpha, eps);

        sensorMemory.update(15);
        ASSERT_NEAR(-0.95, sensorMemory.getGranules()[0].alpha, eps);
        ASSERT_NEAR(0.95, sensorMemory.getGranules()[1].alpha, eps);

        sensorMemory.update(20);
        ASSERT_NEAR(-0.05, sensorMemory.getGranules()[1].alpha, eps);
        ASSERT_NEAR(0.05, sensorMemory.getGranules()[2].alpha, eps);
    }
} // namespace CoreTests