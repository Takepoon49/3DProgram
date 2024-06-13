#pragma once

class PPlane;

class GLaser : public KdGameObject
{
public:

	GLaser() {}
	~GLaser() override {}

	void Init(Math::Vector3 pos, Math::Matrix mat, Math::Vector3 _move, Math::Vector3 _rad);
	void Update()		override;
	void DrawBright()	override;
	void DrawUnLit() override;

private:

	void UpdateMatrix();

	std::shared_ptr<KdModelData> m_spModel;

	Math::Vector3	m_pos;
	Math::Vector3	m_move;
	Math::Vector3	m_rad;
	Math::Matrix	m_rotXMat;
	Math::Matrix	m_rotYMat;
	Math::Matrix	m_rotZMat;
	Math::Matrix	m_TMat;
};