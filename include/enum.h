#pragma once

enum GameStage {
    MainMenu,
    Map,
    Battle
};

enum BattleState {
    PlayerSelectMove,
    EnemySelectMove,
    Targeting,
    PlayingActions
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