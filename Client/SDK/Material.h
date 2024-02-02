#pragma once
#include "MaterialType.h"

class Material {
public:
	MaterialType mMaterialType;
	
	bool isType(MaterialType type) {
		return type == MaterialType::Any || type = this->mMaterialType;
	}
};