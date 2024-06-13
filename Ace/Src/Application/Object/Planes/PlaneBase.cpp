#include "PlaneBase.h"

PlaneBase::PlaneBase()
{

}

PlaneBase::~PlaneBase()
{
	Release();
}

void PlaneBase::Init()
{
	m_spModel = nullptr;
}

void PlaneBase::Update()
{

}

void PlaneBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void PlaneBase::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void PlaneBase::Release()
{
	m_spModel = nullptr;
}
