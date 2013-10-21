#pragma once
#include <SensorMemory.h>
#include "Granule.h"

namespace CoreWrapper
{
	public ref class SensorMemory
	{
	public:

        SensorMemory(double lowerBound, double upperBound, double granuleSize)
        {
            sensorMemory = new Core::SensorMemory(lowerBound, upperBound, granuleSize);
        }

        ~SensorMemory()
        {
            delete sensorMemory;
        }

        void AddLayer(size_t granuleCount)
        {
            sensorMemory->addLayer(granuleCount);
        }

        void RemoveTopLayer()
        {
            sensorMemory->removeTopLayer();
        }

        typedef System::Collections::Generic::List<Granule^> GranuleList;
        GranuleList^ GetGranules(size_t layerIndex)
        {
            std::vector<Core::Granule> granules;
            granules = sensorMemory->getGranules(layerIndex);
            GranuleList ^managedGranules = gcnew GranuleList();
            for(size_t i = 0; i < granules.size(); ++i) {
                managedGranules->Add(gcnew Granule(granules[i].lowerBound,
                    granules[i].upperBound, granules[i].fuzzyFactor));
            }
            return managedGranules;
        }

        void Update(double value)
        {
            sensorMemory->update(value);
        }

	private:
		Core::SensorMemory *sensorMemory;
	};
}
