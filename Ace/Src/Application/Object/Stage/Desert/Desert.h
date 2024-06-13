#pragma once

#include "../StageBase.h"

class Player;

class Desert : public StageBase
{
public:

	Desert();
	~Desert()	override;

	void Init() override;
	void Update() override;
	void DrawLit() override;



private:

	void Release();

	Math::Vector3 m_pos;

	
};