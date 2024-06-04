#pragma once

class Water : public KdGameObject
{
public:

	Water();
	~Water() override;

	void Init(Math::Vector3 pos);
	void Update() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	int m_count;
	int m_anim;
};