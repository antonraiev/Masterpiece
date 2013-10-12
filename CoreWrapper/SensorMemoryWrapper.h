#pragma once
#include "SensorMemory.h"

namespace CoreWrapper
{
	public ref class SensorMemoryWrapper
	{
	public:

		SensorMemoryWrapper()
		{
			sensorMemory = new Core::SensorMemory();
		}

		~SensorMemoryWrapper()
		{
			delete sensorMemory;
		}

		int getSomeValue()
		{
			return sensorMemory->getSomeValue();
		}

	private:
		Core::SensorMemory *sensorMemory;
	};
}
