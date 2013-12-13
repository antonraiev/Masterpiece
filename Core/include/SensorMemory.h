#ifndef SENSORMEMORY_H
#define SENSORMEMORY_H

#include <vector>

#include "Granule.h"

namespace Core 
{
    /** 
    * Represents the information from sensor as a set of granules with fuzzy truth
    * values
    * Allows to enlarge the granules (add additional layer)
    */
    class SensorMemory
    {
    public:
        /** 
        * Create SensorMemory object for one sensor
        * @param lowerBound Lower bound of the sensor value
        * @param upperBound Higher bound of the sensor value
        * @param granuleSize Size of the granule 
        * @param groupSize Amount of granules in group of 0 layer
        */
        explicit SensorMemory(double lowerBound, double upperBound, 
            double granuleSize, size_t groupSize);

        /** 
        * Add a new layer of enlarged granules
        */
        void addLayer();

        /** 
        * Remove the top layer of enlarged grannules
        * It won't work if the only one layer left
        */
        void removeTopLayer();

        /** 
        * Get the amount of layers
        * @returns Amount of layers 
        */
        size_t getLayerCount() const;

        /** 
        * Get the granules of one layer
        * @param layerIndex Index of required layer
        * @returns Vector with granules of the layer 
        */
        std::vector<Granule> getGranules(size_t layerIndex = 0) const;

        /** 
        * Update the sensor memory
        * @param value New value from the sensor */
        void update(double value);

    private:
        Granule createLinkedGranule(const Granule &first, const Granule &second);
        std::vector<size_t> getDifference(size_t firstSetCount, size_t secondSetCount);
        void updateLayer(size_t layerIndex);

    private:
        static const double eps;

        size_t groupSize;
        double granuleSize;
        std::vector<std::vector<Granule> > layers;
        size_t prevCoveredCount;
    };
} // namespace Core

#endif
