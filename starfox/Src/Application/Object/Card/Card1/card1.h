#pragma once

class Card1 : public KdGameObject
{
public:

	Card1() {}
	~Card1() override {}

	void Init() override;
	void Update() override;
	void DrawLit() override;
	//void DrawBright() override;

	void SetCamMat(Math::Matrix* mat) { m_camMat = mat; }

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly;

	Math::Matrix* m_camMat;
};