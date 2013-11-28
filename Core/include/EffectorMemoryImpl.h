#ifndef EFFECTORMEMORYIMPL_H
#define EFFECTORMEMORYIMPL_H

#include "Granule.h"
#include "IFuzzyController.h"

namespace Core 
{
    /** 
    * Computes and holds the resulting control signals using rule activities
    */
    template <typename TControlType>
    class EffectorMemory
    {
    public:
        /** 
        * Create effector memory
        * @param fuzzyController Reference to mediator
        */
        explicit EffectorMemory(IFuzzyController<TControlType> *fuzzyController)
        {
            this->fuzzyController = fuzzyController;

            for(TControlType type = TControlType::First; 
                type != TControlType::Last; ++type) {
                    control[type] = Granule(0, 0, 0);
            }
        }

        /** 
        * Get the control signal for specified control type
        * @param type Type of control
        */
        Granule& getControl(TControlType type) const
        {
            return Granule(0, 0, 0);
        }

        /** 
        * Update the effector memory and recompute all control signals 
        */
        void update()
        {
        }

    private:
        std::map<TControlType, Granule> control;
        IFuzzyController<TControlType> *fuzzyController;
    };
} // namespace Core

#endif
