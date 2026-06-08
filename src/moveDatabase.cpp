#include "../include/moveDataBase.h"

MoveDatabase::MoveDatabase() {
        registry[Tackle]      = {"Tackle", Tackle, 40, 0, 35, Physical};
        registry[QuickPunch]  = {"Quick Punch", QuickPunch, 40, 0, 30, Physical};
        registry[ArmThrust]     = {"Low Kick", ArmThrust, 60, 0, 20, Physical};
        registry[CloseCombat] = {"Close Combat", CloseCombat, 120, 0, 5, Physical};
    }

MoveInstance MoveDatabase::createInstance(MoveName name) const {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return MoveInstance{ &it->second, it->second.uses };
        }
        std::cerr << "CRITICAL: Attempted to build non-existent move ID! "<< (int)name << std::endl;;
        return MoveInstance{};
    }