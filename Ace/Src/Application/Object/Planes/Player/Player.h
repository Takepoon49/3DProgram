#pragma once

#include "../PlaneBase.h"

class Player : public PlaneBase
{
public:

	Player();
	~Player() override;

	void Init() override;
	void Update() override;

	float const GetSpd() { return m_spd; }
	float const GetSpdX() { return m_spdX; }

	float* GetSpdA() { return &m_spd; }
	Math::Vector3 GetDir() { return m_dir; }
	Math::Vector3 GetDeg() { return m_deg; }

private:

	void UpdateMove();
	void UpdateMove1();

	enum key
	{
		kNone = 0 << 0,
		kW = 1 << 1,
		kA = 1 << 2,
		kS = 1 << 3,
		kD = 1 << 4
	};

	enum
	{
		None,
		Throttle,
		Brake,
		PitchUp,
		PitchDown,
		RollLeft,
		RollRight,
		YawLeft,
		YawRight,
		k_end
	};
	UINT m_keyFlg;
	UINT m_key[k_end];

	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
	float m_spd;
	float m_spdX;
	Math::Vector3 m_deg;

	bool m_bSpeedLock;

	Math::Matrix m_rotXMat;
	Math::Matrix m_rotYMat;
	Math::Matrix m_rotZMat;
	Math::Matrix m_transMat;
};