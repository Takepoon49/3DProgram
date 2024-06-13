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

	void DrawDebug() override;

	int GetInt() { return (int)m_rollFlg; }
	float GetFloat() { return m_rot.z; }

	// 方向
	Math::Vector3 GetPos() { return m_pos; }
	Math::Vector3 GetDir() { return m_dir; }
	Math::Vector3 GetRot() { return m_rot; }

	// シーカーに渡す用
	Math::Vector3 GetSeekerPos(int num);
private:

	void UpdateMove();
	void UpdateMove2();
	void UpdateMove3();

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3	m_pos;
	Math::Vector3	m_dir;
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
		ingRight,
	}m_rollFlg;
	int			m_rollCnt;
	int			m_rollWaitTime;

	enum class loop
	{
		normal,
		WaitLoop,
		ingLoop
	}m_loopFlg;
	int			m_loopCnt;
	int			m_loopWaitTime;

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