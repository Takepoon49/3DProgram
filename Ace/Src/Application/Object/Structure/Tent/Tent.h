#pragma once

#include "../StructBase.h"

class Tent : public StructBase
{
public:

	Tent();
	~Tent() override;

	void Init() override;
	void Update() override;

	void OnHit() override;

private:



};