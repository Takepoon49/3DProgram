#pragma once

class Heli : public KdGameObject
{
public:

	Heli();
	~Heli() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;

	Math::Vector3 GetRot() { return m_rot; }
	Math::Vector3 GetSpd() { return m_moveSpd; }
	Math::Vector3 GetVec() { return m_moveVec; }

private:

	void UpdateMoveA();
	void UpdateMoveB();

	std::shared_ptr<KdModelData> m_spModel;

	Math::Vector3	m_pos;
	Math::Vector3	m_rot;
	Math::Vector3	m_moveSpd;
	Math::Vector3	m_moveVec;

	Math::Matrix m_mScale;
	Math::Matrix m_mRotX;
	Math::Matrix m_mRotY;
	Math::Matrix m_mRotZ;
	Math::Matrix m_mTrans;


	enum
	{
		ThrottleUp,
		ThrottleDown,
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