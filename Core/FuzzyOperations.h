#ifndef FUZZYOPERATIONS_H
#define FUZZYOPERATIONS_H

namespace Core
{
    namespace Fuzzy
    {
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
         * Truth accumulation of beta parameter (actuality 
         * of granule information)
         * @param beta1 First beta parameter
         * @param beta2 Second beta parameter
         * @returns Accumulated beta
         */
        double betaAccumulation(double beta1, double beta2);

        /*
         * Resolution of the granule
         * @param beta Beta value of granule
         * @returns Resolution of the granule
         */
        double gamma(double beta);
    }
}

#endif

