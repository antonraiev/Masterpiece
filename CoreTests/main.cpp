#include "gtest/gtest.h"

#include "SensorMemoryTests.h"
#include "FuzzyOperationsTests.h"

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}