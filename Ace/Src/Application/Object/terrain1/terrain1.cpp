#include "terrain1.h"

void Terrain1::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Terrain/teraA0.gltf");
	
	m_pos = { 0.0f, 1.0f, 15.0f };

	Math::Matrix _TMat =
		Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _TMat;
}

void Terrain1::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
