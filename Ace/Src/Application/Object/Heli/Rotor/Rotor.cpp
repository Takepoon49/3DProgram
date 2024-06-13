#include "Rotor.h"

Rotor::Rotor()
{

}

Rotor::~Rotor()
{
	
}

void Rotor::Init()
{
	m_spModel = nullptr;
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Heli/Rotor/Rotor.gltf");
	//m_spModel->Load("Asset/Models/Heli/Heli.gltf");

	m_pos = { 0, 0.35f, 0 };
	m_angle = { 0, 0, 0 };
}

void Rotor::Update()
{
	m_angle.y += 20.0f;
	if (m_angle.y >= 360.0f) { m_angle.y = 0.0f; }

	m_mScale = Math::Matrix::CreateScale(1.0f);

	m_mRotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angle.x));
	m_mRotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle.y));
	m_mRotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle.z));

	if (m_wpParent.expired() == false)
	{
		m_mPare = m_wpParent.lock()->GetMatrix();
	}

	m_mTrans = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_mScale * m_mRotX * m_mRotY * m_mRotZ * m_mTrans * m_mPare;
}

void Rotor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
