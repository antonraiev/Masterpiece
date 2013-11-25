#ifndef EFFECTORMEMORY_H
#define EFFECTORMEMORY_H

#include "Granule.h"
#include "IFuzzyController.h"

namespace Core 
{
    /** 
    * Computes and holds the resulting control signals using rule activities 
    */
    class EffectorMemory
    {
    public:
        /** 
        * Create effector memory
        * @param fuzzyController Reference to mediator
        */
        explicit EffectorMemory(IFuzzyController* fuzzyController);

        /** 
        * Get the control signal for specified control type
        * @param type Type of control
        */
        Granule& getControl(ControlType type) const;

        /** 
        * Update the effector memory and recompute all control signals 
        */
        void update();

    private:
        std::map<ControlType, Granule> control;
        IFuzzyController *fuzzyController;
    };
} // namespace Core

#endif
