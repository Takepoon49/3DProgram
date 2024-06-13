#include "Heli.h"

Heli::Heli()
{

}

Heli::~Heli()
{

}

void Heli::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Heli/Heli.gltf");

	m_pos = { 0, 1.5f, 0 };
	m_rot = { 0, 0, 0 };
	m_moveSpd = {};	// 速度

	// 行列更新
	m_mScale = Math::Matrix::CreateScale(1.0f);
	m_mRotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rot.x));
	m_mRotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	m_mRotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	m_mTrans = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成
	m_mWorld = m_mScale * m_mRotX * m_mRotY * m_mRotZ * m_mTrans;

	// 操作方法
	m_key[ThrottleUp]	= 'W';		// 加速
	m_key[ThrottleDown]	= 'S';		// 減速
	m_key[PitchUp]		= VK_UP;	// ピッチアップ	
	m_key[PitchDown]	= VK_DOWN;	// ピッチダウン
	m_key[RollLeft]		= VK_LEFT;	// 左ロール
	m_key[RollRight]	= VK_RIGHT;	// 右ロール
	m_key[YawLeft]		= 'Q';		// ヨー左
	m_key[YawRight]		= 'E';		// ヨー右

	// キーフラグ
	for (bool& flg : m_keyFlg)
	{
		flg = false;
	}

	// デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Heli::Update()
{
	m_moveVec = Math::Vector3::Zero;

	//UpdateMoveA();
	UpdateMoveB();

	// 座標更新
	m_moveVec.Normalize();		// ベクトル正規化
	m_moveVec *= m_moveSpd;		// ベクトル＊移動速度
	m_pos += m_moveVec;			// 移動処理

	// デバッグ（レイを可視化）
	m_pDebugWire->AddDebugLine(m_pos, m_moveVec, 10.0f, { 1.0f, 0.0f, 0.0f, 1.0f });

	// 行列更新
	m_mScale = Math::Matrix::CreateScale(1.0f);
	m_mRotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rot.x));
	m_mRotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	m_mRotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	m_mTrans = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成
	m_mWorld = m_mScale * m_mRotX * m_mRotY * m_mRotZ * m_mTrans;
}

void Heli::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Heli::UpdateMoveA()
{
	// 出力
	if (GetAsyncKeyState(m_key[ThrottleUp]) & 0x8000)
	{
		m_moveVec.y = +1.0f;
	}
	if (GetAsyncKeyState(m_key[ThrottleDown]) & 0x8000)
	{
		m_moveVec.y = -1.0f;
	}
	// ヨー
	if (GetAsyncKeyState(m_key[YawLeft]) & 0x8000)
	{
		m_rot.y -= 3.0f;
	}
	if (GetAsyncKeyState(m_key[YawRight]) & 0x8000)
	{
		m_rot.y += 3.0f;
	}
	// ピッチ
	if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	{
		m_rot.x += 3.0f;
	}
	if (GetAsyncKeyState(m_key[PitchDown]) & 0x8000)
	{
		m_rot.x -= 3.0f;
	}
	// ロール
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		m_rot.z += 3.0f;
	}
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{
		m_rot.z -= 3.0f;
	}
}

void Heli::UpdateMoveB()
{
	m_rot *= 0.5f;

	// - Z軸 移動 --------------------------------------------
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVec.z = 1.0f;
		if (m_moveVec.z >= 1.0f) m_moveVec.z = 1.0f;

		m_moveSpd.z += 0.01f;
		
		m_rot.x = +30.0f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVec.z = -1.0f;
		if (m_moveVec.z <= -1.0f) m_moveVec.z = -1.0f;
		
		m_moveSpd.z += 0.01f;

		m_rot.x = -30.0f;
	}
	else
	{
		m_moveSpd.z *= 0.93f;
		if (m_moveSpd.z >= -0.01f && m_moveSpd.z <= 0.01f)
		{
			m_moveSpd.z = 0.0f;
			m_moveVec.z = 0.0f;
		}
	}

	// - X軸 移動 --------------------------------------------
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVec.x = -1.0f;
		//if (m_moveVec.x <= -1.0f) m_moveVec.x = -1.0f;
		
		m_moveSpd.x += 0.01f;
		
		
		m_rot.z = +30.0f;
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVec.x = 1.0f;
		if (m_moveVec.x >= 1.0f) m_moveVec.x = 1.0f;
		
		m_moveSpd.x += 0.01f;
		
		m_rot.z = -30.0f;
	}
	else
	{
		m_moveSpd.x *= 0.93f;
		if (m_moveSpd.x >= -0.01f && m_moveSpd.x <= 0.01f)
		{
			m_moveSpd.x = 0.0f;
		}
	}
}
