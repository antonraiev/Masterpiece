#ifndef IFUZZYCONTROLLER_H
#define IFUZZYCONTROLLER_H

#include "Granule.h"
#include "Sensor.h"

#include <map>

namespace Core 
{
    enum ControlType {MOVE_FORWARD, MOVE_BACKWARD};

    /** 
    * Mediator interface. Needed to carry out callbacks from colleagues to mediator 
    */
    class IFuzzyController
    {
    public:
        /** 
        * Get the granule from sensor memory
        * @param type Type of sensor
        * @param layer Layer of granules
        * @param index Index of granule in layer
        * @returns Granule from sensor memory
        */
        virtual Granule getSensorGranule(SensorType type, 
            size_t layer, size_t index) const = 0;

        /** 
        * Get rule activity and control from prototype memory
        * @param type Type of control
        * @returns Map with granule pairs activity-control
        */
        virtual std::map<Granule, Granule> 
            getRuleActivity(ControlType type) const = 0;
    };
} // namespace Core

#endif
