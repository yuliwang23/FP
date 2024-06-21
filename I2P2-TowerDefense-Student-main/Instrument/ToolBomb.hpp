//
// Created by IRIS0817 on 2024/6/13.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TOOLBOMB_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TOOLBOMB_HPP


#include <allegro5/base.h>
#include <list>

#include "Instrument.hpp"

namespace Engine {
    struct Point;
}  // namespace Engine

class ToolBomb : public Instrument{
protected:
    //const float rotateRadian = 2 * ALLEGRO_PI;
    //std::list<Bullet*>::iterator lockedBulletIterator;
public:
    explicit ToolBomb(int x,int y);
    virtual void Update(float deltaTime) override;
    void OnExplode() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TOOLBOMB_HPP