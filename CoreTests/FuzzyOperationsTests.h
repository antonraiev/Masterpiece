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

    TEST(FuzzyOperationsTests, testBetaAccumulation)
    {
        double beta1, beta2;
        const double eps = 0.001;

        beta1 = beta2 = 0.05;
        double result = Core::Fuzzy::betaAccumulation(beta1, beta2);
        ASSERT_NEAR(0.05, result, eps);

        beta1 = beta2 = 25;
        result = Core::Fuzzy::betaAccumulation(beta1, beta2);
        ASSERT_NEAR(25, result, eps);

        beta1 = beta2 = 25;
        result = Core::Fuzzy::betaAccumulation(beta1, beta2);
        ASSERT_NEAR(25, result, eps);
    }
}