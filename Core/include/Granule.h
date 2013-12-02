#ifndef GRANULE_H
#define GRANULE_H

namespace Core 
{
    /** 
    * Represents one granule with bounds and a fuzzy truth value
    */
    struct Granule
    {
        double lowerBound;
        double upperBound;
        double alpha;
        double beta;

        Granule()
        {
        }

        Granule(double alpha, double beta) :
            alpha(alpha),
            beta(beta)
        {
        }

        Granule(double lowerBound, double upperBound, double alpha,
            double beta) :
            lowerBound(lowerBound),
            upperBound(upperBound),
            alpha(alpha),
            beta(beta)
        {
        }
    };
} // namespace Core

#endif /* GRANULE_H */
