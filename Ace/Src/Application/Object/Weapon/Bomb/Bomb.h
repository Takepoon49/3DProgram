#pragma once

#include "../WeaponBase.h"

class Bomb : public WeaponBase
{
public:

	Bomb();
	~Bomb() override;

	void Init() override;
	void Update() override;

	void OnHit() override;

	void SetMatrix(Math::Matrix matrix);

private:

};