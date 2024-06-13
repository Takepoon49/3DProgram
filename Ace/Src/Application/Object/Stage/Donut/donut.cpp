#include "donut.h"

void Donut::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Donut/donut.gltf");

	m_pos.x = m_makePosX[m_makeType];
	m_pos.y = m_makePosY[m_makeType];
	m_pos.z = m_makePosZ[m_makeType];
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
	m_pos.z -= 0.065f + *m_playerSpeed;
	if (m_pos.z <= -9.0f)
	{
		m_pos.z = 60.0f;
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
