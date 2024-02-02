#pragma once

#include "../Math.h"

struct StateVectorComponent
{
	Vec3<float> currentPos;
	Vec3<float> oldPos; 
	Vec3<float> velocity;
};