#ifndef WHEATLANT_HPP
#define WHEATPLANT_HPP
#include "Plant.hpp"

class WheatPlant: public Plant {
public:
	static const int HarvestTime;
    WheatPlant(float x, float y);
	void CreateBullet() override;
};
#endif // WHEATPLANT_HPP
