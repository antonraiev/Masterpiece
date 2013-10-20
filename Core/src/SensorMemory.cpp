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
        for(double d = lowerBound; d <= upperBound; ) {
            Granule granule(d, d = std::min(upperBound, d + granuleSize), -1);
            granules.push_back(granule);
        }
        layers.push_back(granules);
    }

    void SensorMemory::addLayer(size_t granuleCount)
    {
        if(granuleCount > layers.back().size()) {
            throw std::exception("The amount of granules to use for the new layer"
                " should be not greater than the amount of granules in previous layer");
        }

        std::vector<Granule> granules;
        for(size_t i = 0; i < layers.back().size(); ) {
            double maxFuzzyFactor = std::max_element(layers.back().begin() + i,
                layers.back().begin() + i + granuleCount,
                [] (const Granule &first, const Granule &second) -> bool
            {
                return first.fuzzyFactor < second.fuzzyFactor;
            })->fuzzyFactor;
            Granule granule(i, i += granuleCount, maxFuzzyFactor);
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

    }
} // namespace Core
