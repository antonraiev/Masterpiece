#include <ControlModel.h>

#include "Sensor.h"
#include "SensorMemory.h"

namespace CoreWrapper
{
    public ref class ControlModel
    {
    public:

        ControlModel(Sensor ^sensor, double granuleSize)
        {
            controlModel = new Core::ControlModel(sensor->Native, granuleSize);
        }

        ~ControlModel()
        {
            delete controlModel;
        }

        property const Sensor^ Sensor
        {
            const CoreWrapper::Sensor^ get()
            {
                return gcnew CoreWrapper::Sensor(controlModel->getSensor());
            }
        }

        property const SensorMemory^ SensorMemory
        {
            const CoreWrapper::SensorMemory^ get()
            {
                return gcnew CoreWrapper::SensorMemory(
                    controlModel->getSensorMemory());
            }
        }

        void Update()
        {
            controlModel->update();
        }

    private:
        Core::ControlModel *controlModel;
    };
} // namespace CoreWrapper