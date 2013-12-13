#pragma once
#include <SensorMemory.h>
#include "Granule.h"

namespace CoreWrapper
{
	public ref class SensorMemory
	{
	public:

        SensorMemory(double lowerBound, double upperBound, double granuleSize, size_t groupSize)
        {
            sensorMemory = new Core::SensorMemory(lowerBound, upperBound, granuleSize, groupSize);
        }

        ~SensorMemory()
        {
            delete sensorMemory;
        }

        void AddLayer()
        {
            sensorMemory->addLayer();
        }

        void RemoveTopLayer()
        {
            sensorMemory->removeTopLayer();
        }

        property size_t LayerCount
        {
            size_t get()
            {
                return sensorMemory->getLayerCount();
            }
        }

        typedef System::Collections::Generic::List<Granule^> GranuleList;
        GranuleList^ GetGranules(size_t layerIndex)
        {
            std::vector<Core::Granule> granules;
            granules = sensorMemory->getGranules(layerIndex);
            GranuleList ^managedGranules = gcnew GranuleList();
            for(size_t i = 0; i < granules.size(); ++i) {
                managedGranules->Add(gcnew Granule(granules[i].getLowerBound(),
                    granules[i].getUpperBound(), granules[i].getAlpha(),
                    granules[i].getBeta()));
            }
            return managedGranules;
        }

        void Update(double value)
        {
            sensorMemory->update(value);
        }

    internal:
        SensorMemory(Core::SensorMemory &nativeMemory)
        {
            sensorMemory = &nativeMemory;
        }

        property const Core::SensorMemory& Native
        {
            const Core::SensorMemory& get()
            {
                return *sensorMemory;
            }
        }

	private:
		Core::SensorMemory *sensorMemory;
	};
}
