#include "SensorMemory.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <numeric>

#include "FuzzyOperations.h"

namespace Core 
{
    const double SensorMemory::eps = 0.05;

    SensorMemory::SensorMemory(double lowerBound, double upperBound, 
            double granuleSize, size_t groupSize) :
        groupSize(groupSize),
        granuleSize(granuleSize)
    {
        if(upperBound <= lowerBound) {
            throw std::invalid_argument("Upper bound should be greater than lower bound");
        }

        prevCoveredCount = 0;
        std::vector<Granule> granules;
        for(double d = lowerBound; d < upperBound; ) {
            double granuleLowerBound = d;
            d = std::min(upperBound, d + granuleSize);
            Granule granule(granuleLowerBound, d, Fuzzy::MIN_ALPHA, Fuzzy::MAX_BETA);
            granules.push_back(granule);
        }
        layers.push_back(granules);
    }

    void SensorMemory::addLayer()
    {
        const std::vector<Granule> &prevLayer = layers.back();
        if(prevLayer.size() <= 1)
        {
            throw std::runtime_error("Maximum amount of layers reached");
        }
        const size_t layerIndex = layers.size();

        std::vector<Granule> granules;
        if(layerIndex < groupSize) 
        {
            const size_t groupCount = layers[0].size() / groupSize;
            const size_t granuleCount = (groupSize - layerIndex);
            for(size_t i = 0; i < groupCount; ++i)
            {
                const size_t groupIndex = i * (groupSize - layerIndex + 1);
                for(size_t j = groupIndex; j < groupIndex + granuleCount; ++j)
                {
                    granules.push_back(this->createLinkedGranule(prevLayer[j], prevLayer[j+1]));
                }
            }
        } 
        else 
        {
            const size_t granuleCount = prevLayer.size() - 1;
            for(size_t i = 0; i < granuleCount; ++i) {
                granules.push_back(this->createLinkedGranule(prevLayer[i], prevLayer[i+1]));
            }
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
        const size_t currentCoveredCount = static_cast<size_t>(
            std::fabs(value / granuleSize)) + 1;

        // find indices of difference
        std::vector<size_t> currentPrevDifference = this->getDifference(
            currentCoveredCount, prevCoveredCount);
        std::vector<size_t> prevCurrentDifference = this->getDifference(
            prevCoveredCount, currentCoveredCount);

        // update aplha and beta parameters of 0 layer
        std::vector<Granule> &bottomLayer = layers.front();
        for(size_t i = 0; i <bottomLayer.size(); ++i) 
        {
            if(std::find(currentPrevDifference.begin(), currentPrevDifference.end(), i) 
                != currentPrevDifference.end() && currentCoveredCount > prevCoveredCount) 
            {
                bottomLayer[i].setAlpha(Fuzzy::MAX_ALPHA - eps);
                bottomLayer[i].setBeta(Fuzzy::MIN_BETA + eps);
            } 
            else if (std::find(prevCurrentDifference.begin(), prevCurrentDifference.end(), i) 
                != prevCurrentDifference.end() && currentCoveredCount < prevCoveredCount) 
            {
                bottomLayer[i].setAlpha(Fuzzy::MIN_ALPHA + eps);
                bottomLayer[i].setBeta(Fuzzy::MIN_BETA + eps);
            } else {
                bottomLayer[i].setBeta(std::min(bottomLayer[i].getBeta() + Fuzzy::BETA_DELTA,
                    Fuzzy::MAX_BETA));
            }
        }

        // update layers 1-n
        for(size_t i = 1; i < layers.size(); ++i)
        {
            this->updateLayer(i);
        }
        prevCoveredCount = currentCoveredCount;
    }

    Granule SensorMemory::createLinkedGranule(const Granule &first, const Granule &second)
    {
            Granule granule(first.getLowerBound(), second.getUpperBound(),
                Fuzzy::MIN_ALPHA, Fuzzy::MAX_BETA);
            granule.linkPrevLayerGranule(first);
            granule.linkPrevLayerGranule(second);
            return granule;
    }

    std::vector<size_t> SensorMemory::getDifference(size_t firstSetCount, size_t secondSetCount)
    {
        // fill vectors with indices from 0 to setCount
        std::vector<size_t> firstSet(firstSetCount);
        std::iota(firstSet.begin(), firstSet.end(), 0);
        std::vector<size_t> secondSet(secondSetCount);
        std::iota(secondSet.begin(), secondSet.end(), 0);

        // find difference
        std::vector<size_t> difference;
        std::set_difference(firstSet.begin(), firstSet.end(),
            secondSet.begin(), secondSet.end(), std::inserter(
            difference, difference.end()));
        return difference;
    }

    void SensorMemory::updateLayer(size_t layerIndex)
    {
        std::vector<Granule> &layer = layers[layerIndex];
        for(size_t i = 0; i < layer.size(); ++i) 
        {
            Granule &currentGranule = layer[i];
            const std::vector<const Granule*> linkedGranules = currentGranule.getLinkedGranules();
            double linkedAlphaSum = 0;
            double linkedBeta = Fuzzy::MAX_BETA;
            for(size_t j = 0; j < linkedGranules.size(); ++j)
            {
                linkedAlphaSum += linkedGranules[j]->getAlpha();
                linkedBeta = std::min(linkedBeta, linkedGranules[j]->getBeta());
            }
            currentGranule.setAlpha(linkedAlphaSum / linkedGranules.size());
            currentGranule.setBeta(linkedBeta);
        }
    }
} // namespace Core
