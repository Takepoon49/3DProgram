#include "AfterBurner.h"

AfterBurner::AfterBurner()
{

}

AfterBurner::~AfterBurner()
{

}

void AfterBurner::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Pplane/AfterBurner/AfterBurner.gltf");
}

void AfterBurner::Update()
{

}

void AfterBurner::DrawBright()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
