#pragma once

#include <map>
#include <memory>
#include "enum.h"
#include "enemy.h"
#include "assetsManager.h"

struct EnemyPreset {
    std::string presetName;
    std::vector<Enemies> presetEncounters;
};

class EnemyFactory {
private:
    std::map<Enemies, Enemy> enemyDatabase;
    std::vector<EnemyPreset> presets;
public:
    EnemyFactory(AssetManager& assetManager);
    std::unique_ptr<Entity> spawnEnemy(Enemies type);
    void spawnPreset(std::vector<std::unique_ptr<Entity>>& entities, const int width, const int heigth);
};