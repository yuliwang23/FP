#ifndef APPLEPLANT_HPP
#define APPLEPLANT_HPP
#include "Plant.hpp"

class ApplePlant: public Plant {
public:
	static const int HarvestTime;
    ApplePlant(float x, float y);
	void CreateBullet() override;
};
#endif // APPLEPLANT_HPP
