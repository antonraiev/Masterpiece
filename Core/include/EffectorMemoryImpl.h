#ifndef EFFECTORMEMORYIMPL_H
#define EFFECTORMEMORYIMPL_H

#include "Granule.h"
#include "IControlMediator.h"
#include "FuzzyOperations.h"

#include <map>
#include <cassert>

namespace Core 
{
    /** 
    * Computes and holds the resulting control signals using rule activities
    * @tparam TSensorType Type of sensor enum
    * @tparam TControlType Type of control enum
    */
    template <typename TSensorType, typename TControlType>
    class EffectorMemory
    {
    public:
        /** 
        * Create effector memory
        * @param fuzzyController Reference to mediator
        */
        explicit EffectorMemory(IControlMediator<TSensorType,
            TControlType> *controlMediator) :
            controlMediator(controlMediator)
        {
            for(TControlType type = TControlType::First; 
                type != TControlType::Last; ++type) {
                    control[type] = Granule();
            }
        }

        /** 
        * Get the control signal for specified control type
        * @param type Type of control
        */
        const Granule& getControl(TControlType type) const
        {
            return control.find(type)->second;
        }

        /** 
        * Update the effector memory and recompute all control signals 
        */
        void update()
        {
            assert(controlMediator && "Mediator is null");

            for(auto &controlPair : control) {

                // Get rule activity from prototype memory for each rule
                std::vector<std::pair<Granule, Granule>> ruleActivities 
                    = controlMediator->getRuleActivity(controlPair.first);
                assert(ruleActivities.size());

                // Get initial alpha and beta from first rule
                const std::pair<Granule, Granule> &firstRuleActivity 
                    = *ruleActivities.begin();
                const Granule &firstActivity = firstRuleActivity.first;
                const Granule &firstControl = firstRuleActivity.second;

                double ovarallAlpha = Fuzzy::operationG(firstActivity.alpha,
                    firstControl.alpha, firstActivity.beta, firstControl.beta);
                double overallBeta = std::max(firstControl.beta,
                    firstActivity.beta);

                for(auto ruleActivity = ++ruleActivities.begin();
                    ruleActivity != ruleActivities.end(); ++ruleActivity) {

                    const Granule &activity = ruleActivity->first;
                    const Granule &control = ruleActivity->second;

                    double gAlpha = Fuzzy::operationG(activity.alpha,
                        control.alpha, activity.beta, control.beta);

                    // Accumulate alpha and beta with other rule activities
                    ovarallAlpha = Fuzzy::alphaAccumulation(ovarallAlpha,
                        gAlpha);
                    overallBeta = std::max(overallBeta, std::max(control.beta,
                        activity.beta));
                }
                controlPair.second.alpha = ovarallAlpha;
                controlPair.second.beta = overallBeta;
            }
        }

    private:
        std::map<TControlType, Granule> control;
        IControlMediator<TSensorType, TControlType> *controlMediator;
    };
} // namespace Core

#endif
