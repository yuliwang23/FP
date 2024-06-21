//
// Created by IRIS0817 on 2024/6/14.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_HAMMEREFFECT_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_HAMMEREFFECT_HPP

#include <allegro5/base.h>
#include <list>

#include "Bomb.hpp"

namespace Engine {
    struct Point;
}  // namespace Engine

class HammerEffect : public Bomb{
protected:
    //const float rotateRadian = 2 * ALLEGRO_PI;
    //std::list<Bullet*>::iterator lockedBulletIterator;
public:
    static bool change;
    static float ticks;
    static int offset;
    static int frameIndex;
    explicit HammerEffect(int x,int y,int t);
    virtual void Update(float deltaTime) override;
    void OnExplode() override;
    virtual void Draw() const override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_HAMMEREFFECT_HPP