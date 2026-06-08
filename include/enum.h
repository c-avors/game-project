#pragma once

enum GameStage {
    MainMenu,
    Map,
    Battle,
    Victory
};

enum BattleState {
    PlayerSelectMove,
    EnemySelectMove,
    Targeting,
    PlayingActions
};

enum AIType {
    Basic,
    Boss
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