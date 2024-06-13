#include "StageBase.h"

StageBase::StageBase()
{

}

StageBase::~StageBase()
{
	Release();
}

void StageBase::Init()
{
	m_spModel = nullptr;
	m_scale = Math::Vector3::One;
}

void StageBase::Update()
{

}

void StageBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void StageBase::Release()
{
	m_spModel = nullptr;
}

