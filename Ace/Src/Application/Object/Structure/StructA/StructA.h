#pragma once

#include "../StructBase.h"

class StructA : public StructBase
{
public:

	StructA();
	~StructA() override;

	void Init() override;

	void OnHit() override;

private:

	void Release();
};