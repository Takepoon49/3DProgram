#include "WeaponBase.h"

WeaponBase::WeaponBase()
{

}

WeaponBase::~WeaponBase()
{
	Release();
}

void WeaponBase::Init()
{
	m_scale = 1.0f;
	m_pos = {};
	m_deg = {};

	UpdateMatrix();
}

void WeaponBase::Update()
{

}

void WeaponBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void WeaponBase::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void WeaponBase::Release()
{
	m_spModel = nullptr;
}

void WeaponBase::UpdateMatrix()
{
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_rotXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_deg.x));
	m_rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_deg.y));
	m_rotZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg.z));
	m_transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_scaleMat * m_rotXMat * m_rotYMat * m_rotZMat * m_transMat;
}