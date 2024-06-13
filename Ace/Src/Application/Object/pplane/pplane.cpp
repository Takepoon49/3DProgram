#include "pplane.h"

void PPlane::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Pplane/pplane.gltf");

	m_pos		= { 0.0f, 2.5f, 0.0f };		// 座標初期化
	m_dir		= { 0, 0, 1 };				// 向き初期化

	m_rot		= Math::Vector3::Zero;		// 角度初期化
	
	m_rotMax2	= { 40.0f, 45.0f, 40.0f };	// 角度最大値セット
	m_rotMax	= m_rotMax;					// 角度
	
	m_spd[0] = 0.13f;
	m_spd[1] = 0.13f;
	m_moveSpd	= m_spd[0];					// 移動速度初期化

	// ローリング
	m_rollCnt = 0;
	m_rollWaitTime = 12;
	m_rollFlg = roll::normal;

	// ループ
	m_loopCnt = 0;
	m_loopWaitTime = 10;
	m_loopFlg = loop::normal;

	// 操作キー設定
	m_key[Throttle]		= 'W';	// 加速
	m_key[Brake]		= 'S';	// 減速
	m_key[PitchUp]		= 'W';	// ピッチアップ
	m_key[PitchDown]	= 'S';	// ピッチダウン
	m_key[RollLeft]		= 'A';	// 左ロール
	m_key[RollRight]	= 'D';	// 右ロール
	m_key[YawLeft]		= 'Q';	// ヨー左
	m_key[YawRight]		= 'E';	// ヨー右

	// キーフラグ
	for (bool& flg : m_keyFlg)
	{
		flg = false;
	}

	// デバッグ
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void PPlane::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos, 0.6f, kGreenColor);

	m_moveVec	= Math::Vector3::Zero;
	//m_rot		= Math::Vector3::Zero;

	// キー入力で上下左右に移動
	//UpdateMove();	// 旧
	UpdateMove2();	// 
	//UpdateMove3();

	m_pDebugWire->AddDebugLine(m_pos, m_dir, 80.0f, kWhiteColor);

	m_dir.x = cos(DirectX::XMConvertToRadians(m_rot.z + 90.0f)) * 1.0f;	// 横
	m_dir.y = sin(DirectX::XMConvertToRadians(-m_rot.x)) * 1.0f;		// 高さ
	m_dir.z = sin(DirectX::XMConvertToRadians(m_rot.y + 90.0f)) * 1.0f;	// 奥

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

	// 移動量制御
	if (m_pos.x > +6.0f) m_pos.x = +6.0f;
	if (m_pos.x < -6.0f) m_pos.x = -6.0f;

	// 方向処理

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

void PPlane::DrawDebug()
{
	m_pDebugWire->Draw();
}

Math::Vector3 PPlane::GetSeekerPos(int num)
{
	switch (num)
	{
	case 0:
		return m_pos + m_dir * 40.0f;
		break;

	case 1:
		return m_pos + m_dir * 80.0f;
		break;
	}
}

void PPlane::UpdateMove()
{
	// 加速
	if (GetAsyncKeyState(m_key[Throttle]) & 0x8000)
	{
		//m_moveVec.z = +1.0f;
	}
	// 減速
	if (GetAsyncKeyState(m_key[Brake]) & 0x8000)
	{
		//m_moveVec.z = -1.0f;
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

	// ループ入力
	//if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	//{
	//	if (!m_keyFlg[PitchUp])
	//	{
	//		if (m_loopFlg == loop::normal)
	//		{
	//			m_loopFlg = loop::WaitLoop;	// ２回目待機状態にする
	//		}
	//		else if (m_loopFlg == loop::WaitLoop)	// ２回目待機状態だったら
	//		{
	//			m_loopFlg = loop::ingLoop;	// ２回目押された状態
	//		}
	//	}
	//	m_keyFlg[PitchUp] = true;
	//}
	//else
	//{
	//	m_keyFlg[PitchUp] = false;
	//}

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
		m_rot.y += 3.0f;
		if (m_rollFlg != roll::ingLeft)	// 
		{
			m_rotMax.z = m_rotMax2.z;
			if (m_rot.z <= m_rotMax.z)
			{
				m_rot.z += 3.0f;
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
				m_rot.y += 2.5f;
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

	// ロール
	switch (m_rollFlg)
	{
	case roll::normal:
				
		break;

	// === 左 ============================================================
	case roll::WaitLeft:
		if (m_rollCnt <= m_rollWaitTime)
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

	// === 右 ============================================================
	case roll::WaitRight:
		if (m_rollCnt <= m_rollWaitTime)
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

	// ループ
	switch (m_loopFlg)
	{
	case loop::normal:
		
		break;

	case loop::WaitLoop:
		if (m_loopCnt <= m_loopWaitTime)
		{
			m_loopCnt += 1;
		}
		else
		{
			m_loopFlg = loop::normal;
			m_loopCnt = 0;
		}
		break;

	case loop::ingLoop:
		if (m_rot.x > -360.0f)
		{
			m_rot.x -= 15.0f;
		}
		else
		{
			m_rot.x = 0.0f;
			m_loopFlg = loop::normal;
			m_loopCnt = 0;
		}
		break;
	}
}

void PPlane::UpdateMove2()
{
	//m_rot = {};
	m_rot *= 0.95f;

	float rotSpd = 2.5f;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_rot.x += -rotSpd;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_rot.x += +rotSpd;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_rot.y += -rotSpd;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_rot.y += +rotSpd;
	}

	if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	{
		m_moveVec.y = 1.0f;
		m_rot.x += -rotSpd;
	}
	if (GetAsyncKeyState(m_key[PitchDown]) & 0x8000)
	{
		m_moveVec.y = -1.0f;
		m_rot.x += +rotSpd;
	}
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		m_moveVec.x = -1.0f;
		m_rot.y += -rotSpd;
		m_rot.z += +rotSpd;
	}
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{
		m_moveVec.x = 1.0f;
		m_rot.y += +rotSpd;
		m_rot.z += -rotSpd;
	}

	//if (m_rot.y >= +m_rotMax.y) m_rot.y = +m_rotMax.y;
	//if (m_rot.y <= -m_rotMax.y) m_rot.y = -m_rotMax.y;
}

void PPlane::UpdateMove3()
{
	if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	{
		m_moveVec.x = -1.0f;
	}
	if (GetAsyncKeyState(m_key[YawRight]) & 0x8000)
	{
		m_moveVec.x = +1.0f;
	}
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		m_moveVec.x = -1.0f;
	}
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{
		m_moveVec.x = +1.0f;
	}
}
