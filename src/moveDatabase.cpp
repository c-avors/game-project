#include "../include/moveDataBase.h"

MoveDatabase::MoveDatabase() {
        registry[Tackle]      = {"Tackle", Tackle, 40, 0, 35, Physical};
        registry[QuickPunch]  = {"Quick Punch", QuickPunch, 40, 0, 30, Physical};
        registry[ArmThrust]     = {"Arm Thrust", ArmThrust, 60, 0, 20, Physical};
        registry[CloseCombat] = {"Close Combat", CloseCombat, 120, 0, 5, Physical};
        registry[Constrict] = {"Constrict", Constrict, 80, 0, 40, Physical};
        registry[Wrap] = {"Wrap", Wrap, 70, 0, 30, Physical};
        registry[TentacleWhip] = {"Tentacle Whip", TentacleWhip, 50, 0, 25, Physical};
        registry[Grasp] = {"Grasp", Grasp, 90, 0, 15, Physical};
        registry[MysticBolt] = {"Mystic Bolt", MysticBolt, 45, 0, 30, Special};
        registry[ArcaneBlast] = {"Arcane Blast", ArcaneBlast, 70, 0, 15, Special};
        registry[VoidFlare] = {"Void Flare", VoidFlare, 90, 0, 10, Special};
        registry[StarShower] = {"Star Shower", StarShower, 110, 0, 5, Special};
}

MoveInstance MoveDatabase::createInstance(MoveName name) const {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return MoveInstance{ &it->second, it->second.uses };
        }
        std::cerr << "CRITICAL: Attempted to build non-existent move ID! "<< (int)name << std::endl;;
        return MoveInstance{};
    }