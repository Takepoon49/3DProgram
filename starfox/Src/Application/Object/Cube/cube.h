#pragma once

class Cube : public KdGameObject
{
public:
	Cube();
	~Cube() override;

	void Init(Math::Vector3 _pos);
	void Update() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

private:

	std::shared_ptr<KdModelData> m_spModel;

	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	
	Math::Matrix m_transMat;
};