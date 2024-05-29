#include "Heli.h"

Heli::Heli()
{

}

Heli::~Heli()
{

}

void Heli::Init()
{
	m_rotor.spModel = std::make_shared<KdModelData>();
	m_rotor.spModel->Load("Asset/Models/Heli/rotor.gltf");

	m_rotor.pos = { 0, 1.5f, 0 };
	m_rotor.rot = { 0, 0, 0 };

	m_mWorld = Math::Matrix::CreateTranslation(m_rotor.pos);
}

void Heli::Update()
{
	// 回転処理
	m_rotor.rot.y += 30.0f;
	if (m_rotor.rot.y >= 360.0f) m_rotor.rot.y = 0.0f;

	// 回転行列
	Math::Matrix rYMat =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotor.rot.y));

	// 行列合成
	m_mWorld = rYMat * Math::Matrix::CreateTranslation(m_rotor.pos);
}

void Heli::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_rotor.spModel, m_mWorld);
}
