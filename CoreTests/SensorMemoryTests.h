#include <SensorMemory.h>
#include <FuzzyOperations.h>

namespace CoreTests
{
    class SensorMemoryTests : public testing::Test
    {
    public:
        static void checkGranulesEqual(const Core::Granule &expected,
            const Core::Granule &produced)
        {
            ASSERT_EQ(expected.getLowerBound(), produced.getLowerBound());
            ASSERT_EQ(expected.getUpperBound(), produced.getUpperBound());
            ASSERT_EQ(expected.getAlpha(), produced.getAlpha());
            ASSERT_EQ(expected.getBeta(), produced.getBeta());
        }
    };

    TEST_F(SensorMemoryTests, testCreation)
    {
        using Core::Granule;
        Core::SensorMemory sensorMemory(0, 15, 3, 3);
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
        Core::SensorMemory sensorMemory(0, 7.5, 2.5, 3);
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
        Core::SensorMemory sensorMemory(0, 24, 2, 3);
        sensorMemory.addLayer();
        ASSERT_EQ(sensorMemory.getLayerCount(), 2);

        std::vector<Granule> granules = sensorMemory.getGranules(1);
        ASSERT_EQ(8, granules.size());
        Granule expectedGranules[] = 
        {
            Granule(0, 4, -1, 25),
            Granule(2, 6, -1, 25),
            Granule(6, 10, -1, 25),
            Granule(8, 12, -1, 25),
            Granule(12, 16, -1, 25),
            Granule(14, 18, -1, 25),
            Granule(18, 22, -1, 25),
            Granule(20, 24, -1, 25),
        };
        for(size_t i = 0; i < granules.size(); ++i) {
            this->checkGranulesEqual(expectedGranules[i], granules[i]);
        }

        sensorMemory.addLayer();
        granules = sensorMemory.getGranules(2);
        ASSERT_EQ(4, granules.size());
        sensorMemory.addLayer();
        granules = sensorMemory.getGranules(3);
        ASSERT_EQ(3, granules.size());
    }

    TEST_F(SensorMemoryTests, testRemoveTopLayer)
    {
        Core::SensorMemory sensorMemory(5, 15, 1, 2);
        ASSERT_THROW(sensorMemory.removeTopLayer(), std::runtime_error);

        sensorMemory.addLayer();
        sensorMemory.removeTopLayer();
        ASSERT_EQ(sensorMemory.getLayerCount(), 1);
        ASSERT_THROW(sensorMemory.removeTopLayer(), std::runtime_error);
    }

    TEST_F(SensorMemoryTests, testUpdate)
    {
        double eps = 0.001;
        Core::SensorMemory sensorMemory(0, 6, 2, 3);
        sensorMemory.update(5);
        this->checkGranulesEqual(Core::Granule(0, 2, 0.95, 0.05), sensorMemory.getGranules()[0]);
        this->checkGranulesEqual(Core::Granule(2, 4, 0.95, 0.05), sensorMemory.getGranules()[1]);
        this->checkGranulesEqual(Core::Granule(4, 6, 0.95, 0.05), sensorMemory.getGranules()[2]);

        sensorMemory.update(1);
        this->checkGranulesEqual(Core::Granule(0, 2, 0.95, 2.05), sensorMemory.getGranules()[0]);
        this->checkGranulesEqual(Core::Granule(2, 4, -0.95, 0.05), sensorMemory.getGranules()[1]);
        this->checkGranulesEqual(Core::Granule(4, 6, -0.95, 0.05), sensorMemory.getGranules()[2]);

        sensorMemory.update(3);
        this->checkGranulesEqual(Core::Granule(0, 2, 0.95, 4.05), sensorMemory.getGranules()[0]);
        this->checkGranulesEqual(Core::Granule(2, 4, 0.95, 0.05), sensorMemory.getGranules()[1]);
        this->checkGranulesEqual(Core::Granule(4, 6, -0.95, 2.05), sensorMemory.getGranules()[2]);

        sensorMemory.update(0);
        this->checkGranulesEqual(Core::Granule(0, 2, 0.95, 6.05), sensorMemory.getGranules()[0]);
        this->checkGranulesEqual(Core::Granule(2, 4, -0.95, 0.05), sensorMemory.getGranules()[1]);
        this->checkGranulesEqual(Core::Granule(4, 6, -0.95, 4.05), sensorMemory.getGranules()[2]);
    }

    TEST_F(SensorMemoryTests, testUpdateLayers)
    {
        double eps = 0.001;
        Core::SensorMemory sensorMemory(0, 6, 2, 3);
        for(size_t i = 0; i < 2; ++i) {
            sensorMemory.addLayer();
        }
        sensorMemory.update(5);
        this->checkGranulesEqual(Core::Granule(0, 4, 0.95, 0.05), sensorMemory.getGranules(1)[0]);
        this->checkGranulesEqual(Core::Granule(2, 6, 0.95, 0.05), sensorMemory.getGranules(1)[1]);
        this->checkGranulesEqual(Core::Granule(0, 6, 0.95, 0.05), sensorMemory.getGranules(2)[0]);

        sensorMemory.update(3);
        this->checkGranulesEqual(Core::Granule(0, 4, 0.95, 2.05), sensorMemory.getGranules(1)[0]);
        this->checkGranulesEqual(Core::Granule(2, 6, 0, 0.05), sensorMemory.getGranules(1)[1]);
        this->checkGranulesEqual(Core::Granule(0, 6, 0.475, 0.05), sensorMemory.getGranules(2)[0]);
    }
} // namespace CoreTests