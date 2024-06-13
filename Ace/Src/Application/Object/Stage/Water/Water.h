#pragma once

#include "../StageBase.h"

class Water : public StageBase
{
public:

	Water();
	~Water() override;

	void Init() override;
	void Update() override;

private:

	//std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	//int m_count;
	//int m_anim;
};