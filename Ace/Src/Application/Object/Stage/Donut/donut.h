#pragma once

#include "../StageBase.h"

class Donut : public StageBase
{
public:

	Donut(int _mtype) { m_makeType = _mtype; }
	~Donut() override {};

	void Init() override;
	void Update() override;

private:

	float m_makePosX[3] = { -1.9f, +0.0f, +0.0f };
	float m_makePosY[3] = { +1.8f, +1.8f, +1.8f*3.0f };
	float m_makePosZ[3] = { +3.0f, +3.0f*3.0f, +3.0f*3.0f };

	int	m_makeType;

	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
};