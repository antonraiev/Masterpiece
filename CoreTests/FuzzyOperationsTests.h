#include <FuzzyOperations.h>

namespace CoreTests
{
    class FuzzyOperationsTests : public testing::Test
    {
    };

    TEST(FuzzyOperationsTests, testAlphaAccumulation)
    {
        double alpha1, alpha2;
        const double eps = 0.001;

        alpha1 = alpha2 = 1;
        double result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(1, result, eps);

        alpha1 = alpha2 = 0;
        result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(0, result, eps);

        alpha1 = 0.68;
        alpha2 = 0;
        result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(0.68, result, eps);

        alpha1 = 1;
        alpha2 = 0;
        result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(1, result, eps);

        alpha1 = -1;
        alpha2 = -0.1;
        result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(-1, result, eps);

        alpha1 = 1;
        alpha2 = -1;
        result = Core::Fuzzy::alphaAccumulation(alpha1, alpha2);
        ASSERT_NEAR(0, result, eps);
    }

    TEST(FuzzyOperationsTests, testGamma)
    {
        const double eps = 0.0001;
        ASSERT_NEAR(1, Core::Fuzzy::gamma(0.05), eps);
        ASSERT_NEAR(0.95, Core::Fuzzy::gamma(0.06), eps);
        ASSERT_NEAR(0, Core::Fuzzy::gamma(23), eps);
        ASSERT_NEAR(0.9, Core::Fuzzy::gamma(0.15), eps);
        ASSERT_NEAR(0.1, Core::Fuzzy::gamma(2.05), eps);
    }
}