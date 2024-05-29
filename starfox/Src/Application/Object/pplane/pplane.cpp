#include "pplane.h"

void PPlane::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Pplane/pplane.gltf");

	m_pos		= { 0.0f, 1.5f, 0.0f };		// 座標初期化

	m_rot		= Math::Vector3::Zero;		// 角度初期化
	
	m_rotMax2	= { 70.0f, 0.0f, 70.0f };	// 角度最大値セット
	m_rotMax	= m_rotMax;					// 角度
	
	m_spd[0] = 0.07f;
	m_spd[1] = 0.14f;
	m_moveSpd	= m_spd[0];					// 移動速度初期化

	// ローリング
	m_rollCnt = 0;
	m_rollFlg = roll::normal;

	// 操作キー設定
	m_key[Throttle]		= 'W';	// 加速
	m_key[Brake]		= 'S';	// 減速
	m_key[PitchUp]		= VK_UP;
	m_key[PitchDown]	= VK_DOWN;
	m_key[RollLeft]		= 'A';	// 左ロール
	m_key[RollRight]	= 'D';	// 右ロール
	m_key[YawLeft]		= 'Q';	// ヨー左
	m_key[YawRight]		= 'E';	// ヨー右

	// キーフラグ
	for (bool& flg : m_keyFlg)
	{
		flg = false;
	}
}

void PPlane::Update()
{
	m_moveVec	= Math::Vector3::Zero;
	//m_rot		= Math::Vector3::Zero;

	// キー入力で上下左右に移動
	UpdateMove();
	//UpdateMove2();

	Math::Matrix _sMat =
		Math::Matrix::CreateScale(1.0f);
	Math::Matrix _rXMat =
		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rot.x));
	Math::Matrix _rYMat =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	Math::Matrix _rZMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	Math::Matrix _tMat = 
		Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _sMat * _rXMat *_rZMat * _rYMat * _tMat;

	// 移動処理
	m_moveVec.Normalize();		// ベクトル正規化
	m_moveVec *= m_moveSpd;		// ベクトル＊移動速度
	m_pos += m_moveVec;			// 移動処理
}

void PPlane::DrawLit()
//void PPlane::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void PPlane::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void PPlane::UpdateMove()
{
	// 加速
	if (GetAsyncKeyState(m_key[Throttle]) & 0x8000)
	{
		m_moveVec.z = +1.0f;
	}
	// 減速
	if (GetAsyncKeyState(m_key[Brake]) & 0x8000)
	{
		m_moveVec.z = -1.0f;
	}

	// 上昇
	if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	{
		m_moveVec.y = +1.0f;
		if (m_rot.x >= -m_rotMax.x)
		{
			m_rot.x -= 3.0f;
		}
	}
	else
	{
		//if (m_rot.x < 0.0f)
		//{
		//	m_rot.x += 2.0f;
		//}
	}
	// 下降
	if (GetAsyncKeyState(m_key[PitchDown]) & 0x8000)
	{
		m_moveVec.y = -1.0f;
		if (m_rot.x <= m_rotMax.x)
		{
			m_rot.x += 3.0f;
		}
	}
	else
	{
		//if (m_rot.x > 0.0f)
		//{
		//	m_rot.x -= 2.0f;
		//}
	}

	if (!GetAsyncKeyState(m_key[PitchUp]) && !GetAsyncKeyState(m_key[PitchDown]))
	{
		m_rot.x = 0.0f;
	}

	m_rot.y = 0.0f;

	// ==============================================================================
	// - ヨー左 ---------------------------------------------------------
	if (GetAsyncKeyState(m_key[YawLeft]) & 0x8000)
	{	
		m_rot.y = -20.0f;
		//m_moveVec.x = -1.0f;
		if (m_rollFlg != roll::ingLeft)
		{
			if (m_rot.z <= m_rotMax.z)
			{
				m_rot.z += 5.0f;
			}
			if (m_rot.z >= m_rotMax.z) m_rot.z = m_rotMax.z;
		}
	}

	// 左ロール
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		m_moveVec.x = -1.0f;
		if (m_rollCnt == 0)
		{
			if (m_rollFlg != roll::ingLeft)
			{
				m_rotMax.z = m_rotMax2.z;
				if (m_rot.z <= m_rotMax.z)
				{
					m_rot.z += 3.0f;
				}
			}
		}
	}
	else
	{
		if (m_rollFlg != roll::ingLeft)
		{
			m_rotMax.z = m_rotMax2.z/2.0f;
			if (m_rot.z > 0.0f)
			{
				m_rot.z -= 3.0f;
			}
		}
	}
	// 左ロール入力
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		if (!m_keyFlg[RollLeft])
		{
			if (m_rollFlg == roll::normal)
			{
				m_rollFlg = roll::WaitLeft;	// ２回目待機状態にする
			}
			else if (m_rollFlg == roll::WaitLeft)	// ２回目待機状態だったら
			{
				m_rollFlg = roll::ingLeft;	// ２回目押された状態
			}
		}
		m_keyFlg[RollLeft] = true;
	}
	else
	{
		m_keyFlg[RollLeft] = false;
	}
	// ==============================================================================


	// ==============================================================================
	// --- ローリング(右) --------------------------------
	if (GetAsyncKeyState(m_key[YawRight]) & 0x8000)
	{
		m_rot.y = +20.0f;
		//m_moveVec.x = +1.0f;
		if (m_rollFlg != roll::ingRight)
		{
			if (m_rot.z >= -m_rotMax.z)
			{
				m_rot.z -= 5.0f;
			}
			if (m_rot.z <= -m_rotMax.z) m_rot.z = -m_rotMax.z;
		}
	}
	// 右ロール
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{
		m_moveVec.x = +1.0f;
		if (m_rollFlg != roll::ingRight)
		{
			m_rotMax.z = m_rotMax2.z;
			if (m_rot.z >= -m_rotMax.z)
			{
				m_rot.z -= 3.0f;
			}
		}
	}
	else
	{
		if (m_rollFlg != roll::ingRight)
		{
			m_rotMax.z = m_rotMax2.z / 2.0f;
			if (m_rot.z < 0.0f)
			{
				m_rot.z += 3.0f;
			}
		}
	}
	// 右ロール入力
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{	
		if (!m_keyFlg[RollRight])
		{
			if (m_rollFlg == roll::normal)
			{
				m_rollFlg = roll::WaitRight;	// ２回目待機状態にする
			}
			else if (m_rollFlg == roll::WaitRight)	// ２回目待機状態だったら
			{
				m_rollFlg = roll::ingRight;	// ２回目押された状態
			}
		}
		m_keyFlg[RollRight] = true;
	}
	else
	{
		m_keyFlg[RollRight] = false;
	}
	// ==============================================================================

	// フラグ
	switch (m_rollFlg)
	{
	case roll::normal:
				
		break;

	case roll::WaitLeft:
		if (m_rollCnt <= 14)
		{
			m_rollCnt += 1;
		}
		else
		{
			m_rollFlg = roll::normal;
			m_rollCnt = 0;
		}
		break;

	case roll::ingLeft:
		if (m_rot.z < 360.0f)
		{
			m_rot.z += 15.0f;
		}
		else
		{
			m_rot.z = 0.0f;
			m_rollFlg = roll::normal;
			m_rollCnt = 0;
		}
		break;

	case roll::WaitRight:
		if (m_rollCnt <= 14)
		{
			m_rollCnt += 1;
		}
		else
		{
			m_rollFlg = roll::normal;
			m_rollCnt = 0;
		}
		break;
	case roll::ingRight:
		if (m_rot.z > -360.0f)
		{
			m_rot.z -= 15.0f;
		}
		else
		{
			m_rot.z = 0.0f;
			m_rollFlg = roll::normal;
			m_rollCnt = 0;
		}
		break;
	}
	
	if (GetAsyncKeyState(m_key[YawLeft]) && GetAsyncKeyState(m_key[YawRight]))
	{
		m_moveVec.x = 0.0f;
	}
	if (GetAsyncKeyState(m_key[PitchUp]) && GetAsyncKeyState(m_key[PitchDown]))
	{
		m_moveVec.y = 0.0f;
	}
	if (GetAsyncKeyState(m_key[RollLeft]) || GetAsyncKeyState(m_key[RollRight]))
	{
		m_moveSpd = m_spd[1];
	}
	else
	{
		m_moveSpd = m_spd[0];
	}
}

void PPlane::UpdateMove2()
{
	//if ()
}