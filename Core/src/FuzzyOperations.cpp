#include "FuzzyOperations.h"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace Core
{
    namespace Fuzzy
    {
        double alphaAccumulation(double alpha1, double alpha2,
            double gamma1, double gamma2)
        {
            if(alpha1 >=0 && alpha2 >= 0)
            {
                return alpha1 * gamma1 + alpha2 * gamma2
                    - alpha1 * alpha2 * gamma1 * gamma2;
            } 
            else if(alpha1 < 0 && alpha2 < 0)
            {
                return alpha1 * gamma1 + alpha2 * gamma2
                    + alpha1 * alpha2 * gamma1 * gamma2;
            }
            else
            {
                double denominator = (1 - std::min(std::abs(alpha1) * gamma1,
                        std::abs(alpha2) * gamma2));
                if(denominator == 0) {
                    return 0;
                }

                return (alpha1 * gamma1 + alpha2 * gamma2)
                    / denominator;
            }
        }

        double alphaAccumulation(double alpha1, double alpha2)
        {
            return alphaAccumulation(alpha1, alpha2, 1, 1);
        }

        double gamma(double beta)
        {
            const size_t tableSize = 16;
            double betaValues[tableSize + 1] = {0, 0.05, 0.1, 0.2, 0.4, 0.7, 0.9, 1.05, 1.3, 
                1.7, 2.5, 4, 7, 11, 16, 21, MAX_BETA};
            double gammaValues[tableSize] = {1, 0.95, 0.9, 0.8, 0.7, 0.65, 0.6, 0.5, 
                0.3, 0.1, 0.75, 0.03, 0.02, 0.01, 0.001, 0};

            const double eps = 0.0001;
            for(size_t i = 1; i < tableSize + 1; ++i) {
                if(beta >= betaValues[i - 1] && beta <= betaValues[i]) {
                    return gammaValues[i - 1];
                }
            }
            throw std::invalid_argument("Beta is out of bounds");
        }

        double operationG(double alpha1, double alpha2, double beta1, double beta2)
        {
            if(alpha1 < 0) {
                return - (std::fabs(alpha1) * gamma(beta1) 
                    * std::fabs(alpha2) * gamma(beta2));
            } else {
                return alpha1 * gamma(beta1) 
                    * alpha2 * gamma(beta2);
            }
        }
    }
}
