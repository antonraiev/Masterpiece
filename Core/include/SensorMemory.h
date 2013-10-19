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
        * @param lowerBound The lower bound of thesensor's value
        * @param upperBound The higher bound of the sensor's value
        * @param granuleSize The size of the granule 
        * (upperBound - lowerBound) % granuleSize should be 0
        */
        explicit SensorMemory(double lowerBound, double upperBound, double granuleSize);

        /** 
        * Add a new layer of enlarged granules
        * @param granuleCount Determines how many granules of
        * the previous layer will be used to create one granule for
        * the new layer
        */
        void addLayer(size_t granuleCount);

        /** 
        * Remove the top layer of enlarged grannules
        * It won't work if the only one layer left
        */
        void removeTopLayer();

        /** 
        * Get the amount of layers
        * @returns The amount of layers 
        */
        size_t getLayerCount() const;

        /** 
        * Get the granules of one layer
        * @param layerIndex Index of required layer
        * @returns A vector with granules of the layer 
        */
        std::vector<Granule> getGranules(size_t layerIndex = 0) const;

        /** 
        * Update the sensor memory
        * @param value New value from the sensor */
        void update(double value);

    private:
        /** 
        * The relevance of the information in granules
        * A fuzzy truth value [-1..1]
        */
        float beta;

        std::vector<std::vector<Granule> > layers;
        size_t layerCount;
    };
} // namespace Core

#endif /* SENSORMEMORY_H */
