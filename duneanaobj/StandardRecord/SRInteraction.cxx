#include "duneanaobj/StandardRecord/SRInteraction.h"

namespace caf
{
    bool SRInteraction::contained() const
    {
        for (const auto& p : part.recopart) {
            if (!p.contained) {
                return false;
            }
        }
        // If all particles are contained, return true
        return true;
    }
}
