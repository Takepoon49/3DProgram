#include "cube.h"

Cube::Cube()
{

}

Cube::~Cube()
{

}

void Cube::Init(Math::Vector3 _pos)
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Cube/cube.gltf");

	m_pos = _pos;
	m_pos.y += 1.5f;
	m_rot = {};

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Cube::Update()
{
	m_pos.z -= 0.065f;
	if (m_pos.z <= -3.0f)
	{
		m_pos.z = 40.0f;
	}

	m_transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_transMat;
}

void Cube::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Cube::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
