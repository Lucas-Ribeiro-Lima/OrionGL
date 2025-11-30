#pragma once
#include "Model.h"

struct CorpData {
	MaterialData mat;
	float radius;
	float rotationScaler;
	float translationScaler;
	std::array<float, 3> pos;
};

struct ShadersSrc {
	const char* vertex;
	const char* fragment;
};

class Corp : public Model
{
	float rotationScaler;
	float translationScaler;

public:
	Corp(CorpData &data);
	Corp(CorpData &data, ShadersSrc shaders_src);
	void draw() override;
};

