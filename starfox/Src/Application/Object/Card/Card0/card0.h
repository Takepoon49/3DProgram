#pragma once

class Card0 : public KdGameObject
{
public:

	Card0() {}
	~Card0() override {}

	void Init() override;
	void Update() override;
	void DrawLit() override;
	//void DrawBright() override;

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly;

	Math::Matrix m_mWorld2;

	Math::Vector3 m_pos;
};