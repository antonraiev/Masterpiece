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
        double fuzzyFactor;
    };
} // namespace Core

#endif /* GRANULE_H */
