#ifndef PLANT_HPP
#define PLANT_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class FarmScene;

class Plant: public Engine::Sprite {
protected:
    int harvestTime;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Plant*>::iterator lockedPlantIterator;
    FarmScene* getFarmScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    //Enemy* Target = nullptr;
    Plant(std::string imgBase, std::string imgPlant, float x, float y, float radius, int price, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
    int GetHarvestTime() const;
};
#endif // PLANT_HPP
