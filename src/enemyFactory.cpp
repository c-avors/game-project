#include "../include/enemyFactory.h"
#include <string>

EnemyFactory::EnemyFactory(AssetManager& assetManager) {
    enemyDatabase[Alginnus] = Enemy("Alginnus", assetManager.getTexture("Alginnus"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[Cavalier] = Enemy("Cavalier", assetManager.getTexture("Cavalier"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[Cheerot] = Enemy("Cheerot", assetManager.getTexture("Cheerot"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[Golorch] = Enemy("Golorch", assetManager.getTexture("Golorch"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[Khafiyn] = Enemy("Khafiyn", assetManager.getTexture("Khafiyn"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[LakeDowager] = Enemy("LakeDowager", assetManager.getTexture("LakeDowager"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});
    enemyDatabase[Luminant] = Enemy("Luminant", assetManager.getTexture("Luminant"), 10, 88, 88, 160, 88, 88, {Tackle, Tackle, Tackle, Tackle});

    presets.push_back({"Cheers", {Cheerot, Cheerot, Cheerot}});
    presets.push_back({"Toxapex", {Alginnus, Alginnus}});
}

//spawns single enemy
std::unique_ptr<Entity> EnemyFactory::spawnEnemy(Enemies type) {
    auto it = enemyDatabase.find(type);
    if (it == enemyDatabase.end()) return nullptr;

    const Enemy& enemy = it->second;

    return std::make_unique<Enemy>(enemy);
    
}

void EnemyFactory::spawnPreset(std::vector<std::unique_ptr<Entity>>& entities, const int width, const int heigth) {
    int choice = rand() % presets.size();
    auto chosenPreset = presets[choice];


    float enemyPositionX = 0.65*width;
    float enemyPositionY = heigth-0.125*heigth;

    for (auto &type : chosenPreset.presetEncounters) {
        auto enemy = spawnEnemy(type);
        enemy->setScale({0.25, 0.25});
        enemy->setPosition({enemyPositionX,enemyPositionY-enemy->getGlobalBounds().size.y});
        enemy->setHpBar();
        enemyPositionX+=(enemy->getGlobalBounds().size.x + 50);
        entities.emplace_back(std::move(enemy));
    }
}