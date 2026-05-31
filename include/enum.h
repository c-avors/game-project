#pragma once

enum GameStage {
    MainMenu,
    Map,
    Battle
};

enum MoveName {
    Tackle,
    CloseCombat,
    ArmThrust,
    BulkUp,
    DrainPunch,
    QuickPunch
};

enum Enemies {
    Alginnus,
    Cavalier,
    Cheerot,
    Golorch,
    Khafiyn,
    LakeDowager,
    Luminant
};

enum MoveType {
    Physical,
    Special,
    Status
};

enum Effect {
    None,
    Poison,
    AttackUp,
    VeilUp,
};