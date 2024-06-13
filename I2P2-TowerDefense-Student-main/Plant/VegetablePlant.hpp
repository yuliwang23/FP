#ifndef VEGETABLEPLANT_HPP
#define VEGETABLEPLANT_HPP
#include "Plant.hpp"

class VegetablePlant: public Plant {
public:
	static const int HarvestTime;
    VegetablePlant(float x, float y);
	void CreateBullet() override;
};
#endif // VEGETABLEPLANT_HPP
