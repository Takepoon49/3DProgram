#pragma once

class Seeker : public KdGameObject
{
public:

	Seeker() {}
	~Seeker() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

	Math::Vector3* GetPosA()
	{
		return &m_pos;
	};

	void SetNearPos(Math::Vector3 pos) { m_pos = pos; }
	void SetFarPos(Math::Vector3 pos) { m_farPos = pos; }

private:

	KdTexture		m_tex;

	Math::Vector3	m_pos;
	Math::Vector3	m_farPos;
	float			m_deg;

	float			m_scale;

	Math::Matrix	m_farMat;

	enum key
	{
		k_p,
		k_end
	};
	bool			m_keyFlg[k_end];
};