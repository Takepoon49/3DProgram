#pragma once

class PPlane : public KdGameObject
{
public:

	PPlane() {}
	~PPlane() override {}

	void Init() override;
	void Update() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;
	//void DrawBright() override;

	int GetInt() { return (int)m_rollFlg; }
	float GetFloat() { return m_rot.z; }

private:

	void UpdateMove();
	void UpdateMove2();

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3	m_pos;
	Math::Vector3	m_rot;
	Math::Vector3	m_rotMax;
	Math::Vector3	m_rotMax2;

	float			m_spd[2];
	float			m_moveSpd;
	Math::Vector3	m_moveVec;

	enum class roll
	{
		normal,
		WaitLeft,
		ingLeft,
		WaitRight,
		ingRight
	};
	roll			m_rollFlg;
	float			m_rollCnt;

	enum
	{
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

	int				m_key[k_end];
	bool			m_keyFlg[k_end];
};