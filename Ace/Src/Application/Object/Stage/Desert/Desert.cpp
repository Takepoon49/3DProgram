#include "Desert.h"

Desert::Desert()
{

}

Desert::~Desert()
{
	Release();
}

void Desert::Init()
{
	StageBase::Init();

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Stage/Desert/Desert.gltf");
	}

	m_pos = {};
}

void Desert::Update()
{
	m_pos.z -= 0.1f + *m_playerSpeed;

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(80.0f, 1.0f, 100.0f);

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void Desert::DrawLit()
{
	if (m_spModel)
	{
		//Math::Color color = { 1.00f, 0.79f, 0.53f };
		Math::Color color = { 1.00f, 1.00f, 1.00f };
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld, color);
	}
}

void Desert::Release()
{
	m_spModel = nullptr;
}
