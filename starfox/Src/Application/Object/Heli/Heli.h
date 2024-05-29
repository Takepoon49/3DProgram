#pragma once

class Heli : public KdGameObject
{
public:

	Heli();
	~Heli() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;

private:

	struct
	{
		std::shared_ptr<KdModelData> spModel = nullptr;
		Math::Vector3 pos = {};
		Math::Vector3 rot = {};
	}m_rotor;
};