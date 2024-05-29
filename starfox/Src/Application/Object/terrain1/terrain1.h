#pragma once

class Terrain1 : public KdGameObject
{
public:

	Terrain1() {}
	~Terrain1() override {}

	void Init() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	Math::Vector3 m_pos;

};