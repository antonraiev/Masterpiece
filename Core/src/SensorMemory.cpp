#include "SensorMemory.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>

namespace Core 
{
    SensorMemory::SensorMemory(double lowerBound, double upperBound, double granuleSize) :
        beta(1.f)
    {
        if(upperBound <= lowerBound) {
            throw std::invalid_argument("Upper bound should be greater than lower bound");
        }

        std::vector<Granule> granules;
        for(double d = lowerBound; d < upperBound; ) {
            double granuleLowerBound = d;
            d = std::min(upperBound, d + granuleSize);
            Granule granule(granuleLowerBound, d, -1);
            granules.push_back(granule);
        }
        layers.push_back(granules);
    }

    void SensorMemory::addLayer(size_t granuleCount)
    {
        std::vector<Granule> prevLayer = layers.back();
        if(granuleCount > prevLayer.size()) {
            granuleCount = prevLayer.size();
        }

        std::vector<Granule> granules;

        for(size_t i = 0; i < prevLayer.size(); ++i) {
            size_t nextIndex = std::min(i + granuleCount - 1, prevLayer.size() - 1);
            double maxFuzzyFactor = std::max_element(prevLayer.begin() + i,
                prevLayer.begin() + nextIndex,
                [] (const Granule &first, const Granule &second) -> bool
            {
                return first.fuzzyFactor < second.fuzzyFactor;
            })->fuzzyFactor;

            double granuleLowerBound = prevLayer[i].lowerBound;
            i = nextIndex;
            double granuleUpperBound = prevLayer[i].upperBound;
            Granule granule(granuleLowerBound, granuleUpperBound, maxFuzzyFactor);
            granules.push_back(granule);
        }
        layers.push_back(granules);
    }

    void SensorMemory::removeTopLayer()
    {
        if(layers.size() <= 1) {
            throw std::runtime_error("Can not remove the last layer");
        }
        layers.erase(layers.end() - 1);
    }

    size_t SensorMemory::getLayerCount() const
    {
        return layers.size();
    }

    std::vector<Granule> SensorMemory::getGranules(size_t layerIndex) const
    {
        if(layerIndex >= layers.size()) {
            throw std::invalid_argument("Layer with specified index does not exist");
        }
        return layers[layerIndex];
    }

    void SensorMemory::update(double value)
    {
        double eps = 0.05;
        size_t layerCount = layers.size();
        std::vector<Granule> &bottomLayer = layers.front();

        for(size_t i = 0; i < bottomLayer.size(); ++i) {
            double granuleDelta = bottomLayer[i].upperBound 
                - bottomLayer[i].lowerBound;

            if(value >= bottomLayer[i].lowerBound 
                && value <= bottomLayer[i].lowerBound + granuleDelta / 2) 
            {
                double granuleSigma = bottomLayer[i].lowerBound 
                    + (granuleDelta / 2) - value;
                if(i > 0) {
                    bottomLayer[i-1].fuzzyFactor = (-1 + eps) 
                        + granuleSigma / (granuleDelta / 2);
                }
                bottomLayer[i].fuzzyFactor = (1 - eps) 
                    - (granuleSigma / (granuleDelta / 2));
            } 
            else if(value > bottomLayer[i].lowerBound + granuleDelta / 2
                && value <= bottomLayer[i].upperBound) 
            {
                double granuleSigma = value - (bottomLayer[i].lowerBound 
                    + granuleDelta / 2);
                bottomLayer[i].fuzzyFactor = (1 - granuleSigma / (granuleDelta
                    / 2)) - eps;
                if(i < bottomLayer.size() - 1) {
                    bottomLayer[i+1].fuzzyFactor = (-1 + eps) + granuleSigma
                        / (granuleDelta / 2);
                }
                ++i;
            } else {
                bottomLayer[i].fuzzyFactor = -1 + eps;
            }
        }
    }
} // namespace Core
