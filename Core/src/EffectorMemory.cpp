#include "EffectorMemory.h"

namespace Core
{
    EffectorMemory::EffectorMemory(IFuzzyController* fuzzyController)
    {
    }

    Granule& EffectorMemory::getControl(ControlType type) const
    {
        return Granule(0, 0, 0);
    }

    void EffectorMemory::update()
    {
    }
}
