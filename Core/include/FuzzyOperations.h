#ifndef FUZZYOPERATIONS_H
#define FUZZYOPERATIONS_H

namespace Core
{
    namespace Fuzzy
    {
        static const double MIN_ALPHA = -1;
        static const double MAX_ALPHA = 1;
        static const double MIN_BETA = 0;
        static const double MAX_BETA = 25;
        static const double BETA_DELTA = 2;
        /*
         * Truth accumulation of alpha parameter (fuzzy truth factor of granule)
         * @param alpha1 First alpha parameter
         * @param alpha2 Second alpha parameter
         * @param gamma1 Resolution of first granule (gamma() function 
         * for accosiated beta)
         * @param gamma2 Resolution of second granule (gamma() function
         * for accosiated beta)
         * @returns Accumulated alpha
         */
        double alphaAccumulation(double alpha1, double alpha2,
            double gamma1, double gamma2);

        /*
         * Truth accumulation of alpha parameter (fuzzy truth factor of granule)
         * with gamma1 = gamma2 = 1
         * @param alpha1 First alpha parameter
         * @param alpha2 Second alpha parameter
         * @returns Accumulated alpha
         */
        double alphaAccumulation(double alpha1, double alpha2);

        /*
         * Resolution of the granule
         * @param beta Beta value of granule
         * @returns Resolution of the granule
         */
        double gamma(double beta);

        /*
         * Operation G (compute the truth value of two granules)
         * @param alpha1 Alpha of the first granule
         * @param alpha2 Alpha of the second granule
         * @param beta1 Beta of the first granule
         * @param beta2 Beta of the second granule
         * @returns Overall alpha
         */
        double operationG(double alpha1, double alpha2, double beta1, double beta2);
    }
}

#endif

