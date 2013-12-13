#include "Granule.h"

namespace Core
{
    Granule::Granule() :
        lowerBound(0),
        upperBound(0),
        alpha(0),
        beta(0)
    {
    }

    Granule::Granule(double alpha, double beta) :
        alpha(alpha),
        beta(beta)
    {
    }

    Granule::Granule(double lowerBound, double upperBound, double alpha,
        double beta) :
        lowerBound(lowerBound),
        upperBound(upperBound),
        alpha(alpha),
        beta(beta)
    {
    }

    double Granule::getAlpha() const
    {
        return alpha;
    }

    void Granule::setAlpha(double alpha)
    {
        this->alpha = alpha;
    }

    double Granule::getBeta() const
    {
        return beta;
    }

    void Granule::setBeta(double beta)
    {
        this->beta = beta;
    }

    double Granule::getLowerBound() const
    {
        return lowerBound;
    }

    double Granule::getUpperBound() const
    {
        return upperBound;
    }

    const std::vector<const Granule*>& Granule::getLinkedGranules() const
    {
        return prevLayerLinkedGranules;
    }

    void Granule::linkPrevLayerGranule(const Granule &granule)
    {
        prevLayerLinkedGranules.push_back(&granule);
    }
};
