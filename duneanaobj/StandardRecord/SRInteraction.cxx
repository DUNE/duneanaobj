#include "duneanaobj/StandardRecord/SRInteraction.h"

namespace caf
{
    bool SRInteraction::contained() const
    {
        for (const auto& p : part.spine) {
            if (!p.contained) {
                return false;
            }
        }

        for (const auto& p : part.pandora) {
            if (!p.contained) {
                return false;
            }
        }
        for (const auto& p : part.pida) {
            if (!p.contained) {
                return false;
            }
        }

        // Add other reco stacks as needed
        // If all particles are contained, return true
        return true;
    }
}
