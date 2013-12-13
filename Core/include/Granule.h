#ifndef GRANULE_H
#define GRANULE_H

#include <vector>

namespace Core 
{
    /** 
    * Represents one granule with bounds and a fuzzy truth value
    */
    class Granule
    {
    public:
        Granule();
        Granule(double alpha, double beta);
        Granule(double lowerBound, double upperBound, double alpha, double beta);

        double getAlpha() const;
        void setAlpha(double alpha);
        double getBeta() const;
        void setBeta(double beta);
        double getLowerBound() const;
        double getUpperBound() const;
        const std::vector<const Granule*>& getLinkedGranules() const;
        void linkPrevLayerGranule(const Granule &granule);

    private:
        double lowerBound;
        double upperBound;
        double alpha;
        double beta;

        std::vector<const Granule *> prevLayerLinkedGranules;
    };
} // namespace Core

#endif /* GRANULE_H */
