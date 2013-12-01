#ifndef IFUZZYCONTROLLER_H
#define IFUZZYCONTROLLER_H

#include "Granule.h"

#include <vector>
#include <map>

namespace Core 
{
    /** 
    * Mediator interface. Needed to carry out callbacks from colleagues to mediator 
    * @tparam TSensorType Type of sensor enum
    * @tparam TControlType Type of control enum
    */
    template <typename TSensorType, typename TControlType>
    class IControlMediator
    {
    public:
        /** 
        * Get the granule from sensor memory
        * @param type Type of sensor
        * @param layer Layer of granules
        * @param index Index of granule in layer
        * @returns Granule from sensor memory
        */
        virtual Granule getSensorGranule(TSensorType type, 
            size_t layer, size_t index) const = 0;

        /** 
        * Get rule activity and control from prototype memory
        * @param type Type of control
        * @returns Vector with granule pairs activity-control
        */
        virtual std::vector<std::pair<Granule, Granule> >
            getRuleActivity(TControlType type) const = 0;

        virtual ~IControlMediator(){}
    };
} // namespace Core

#endif
