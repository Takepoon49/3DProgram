#include "StructBase.h"

StructBase::StructBase()
{

}

StructBase::~StructBase()
{
	Release();
}

void StructBase::Init()
{

}

void StructBase::Update()
{

}

void StructBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void StructBase::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void StructBase::SetParameter(Math::Vector3 _pos, Math::Vector3 _rot, float _scale)
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(_scale);
	Math::Vector3 pos = _pos;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(_pos);
	Math::Vector3 rot = _rot;
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rot.x));
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rot.y));
	Math::Matrix rotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rot.z));
	m_mWorld = scaleMat * rotX * rotY * rotZ * transMat;
}

void StructBase::Release()
{
	m_spModel = nullptr;
}
