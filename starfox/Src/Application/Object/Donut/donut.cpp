#include "donut.h"

void Donut::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Donut/donut.gltf");

	m_pos.x = m_makePosX[m_makeType];
	m_pos.y = 1.8f;
	m_pos.z = m_makePosZ[m_makeType];
	
	m_rot = Math::Vector3::Zero;
}

void Donut::Update()
{
	// 回転処理
	m_rot.z += 4.0f;
	if (m_rot.z >= 360.0f)
	{
		m_rot.z -= 360.0f;
	}

	// 移動処理
	m_pos.z -= 0.065f;
	if (m_pos.z <= -3.5f)
	{
		m_pos.z = 24.0f;
	}

	// 行列更新
	Math::Matrix _sMat =
		Math::Matrix::CreateScale(1.5f);
	Math::Matrix _rZMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	Math::Matrix _tMat =
		Math::Matrix::CreateTranslation(m_pos);

	// 行列合成
	m_mWorld = _sMat *_rZMat * _tMat;
}

void Donut::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Donut::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
