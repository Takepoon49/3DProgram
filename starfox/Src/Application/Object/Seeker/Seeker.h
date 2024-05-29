#pragma once

class Seeker : public KdGameObject
{
public:

	Seeker() {}
	~Seeker() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

private:

	KdTexture		m_tex;

	Math::Vector3	m_pos;
	float			m_deg;

	Math::Matrix	m_farMat;

	enum key
	{
		k_p,
		k_end
	};
	bool			m_keyFlg[k_end];
	bool			m_bMouse;
	POINT			m_mousePos;

	void GetMousePos2(POINT* apMousePos);
	void SetMousePos2(int x, int y);
};