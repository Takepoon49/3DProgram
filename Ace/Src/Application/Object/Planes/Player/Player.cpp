#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Pplane/pplane.gltf");

	m_pos = { 0.0f, 5.0f, 0.0f};
	//m_pos = { 0.0f, 10.0f, -110.0f};
	m_dir = { 0, 0, 0 };
	m_spd = 0.12f;
	m_spdX = 0.0f;
	m_deg = {};

	m_bSpeedLock = true;

	m_keyFlg = None;

	m_key[Throttle]		= VK_UP;
	m_key[Brake]		= VK_DOWN;
	
	m_key[PitchUp]		= 'S';
	m_key[PitchDown]	= 'W';
	m_key[RollLeft]		= 'A';
	m_key[RollRight]	= 'D';

	m_key[YawLeft]		= 'Q';
	m_key[YawRight]		= 'E';

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	UpdateMove();

	//m_dir.x = cos(DirectX::XMConvertToRadians( m_deg.z + 90.0f)) * 1.0f;	// 横
	//m_dir.y = sin(DirectX::XMConvertToRadians(-m_deg.x))		 * 1.0f;	// 高さ
	//m_dir.z = sin(DirectX::XMConvertToRadians( m_deg.y + 90.0f)) * 1.0f;	// 奥

	m_pDebugWire->AddDebugLine(m_pos, m_dir, 30.0f, kRedColor);

	m_dir.Normalize();
	//m_pos.x += m_dir.x * m_spdX;
	m_pos.x += m_spdX;

	m_rotXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_deg.x));
	m_rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_deg.y));
	m_rotZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg.z));
	m_transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotXMat * m_rotYMat * m_rotZMat * m_transMat;
}

void Player::UpdateMove()
{
	m_keyFlg = kNone;
	m_dir = Math::Vector3::Zero;

	// 出力
	if (GetAsyncKeyState(m_key[Throttle]) & 0x8000)
	{
		m_spd += 0.005f;

		m_keyFlg += Throttle;
	}
	if (GetAsyncKeyState(m_key[Brake]) & 0x8000)
	{
		m_spd -= 0.005f;

		m_keyFlg += Brake;
	}

	if (m_bSpeedLock)
	{
		// 最高速度
		if (m_spd >= 0.5f)
		{
			m_spd = 0.5f;
		}
		// 最低速度
		if (m_spd <= 0.030f)
		{
			m_spd = 0.030f;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		//m_spd.z += 0.01f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		//m_spd.z -= 0.01f;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		//m_dir.x = -1.0f;
		
		m_keyFlg |= kA;

		m_spdX -= 0.03f;
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		//m_dir.x = +1.0f;
		
		m_keyFlg |= kD;

		m_spdX += 0.03f;
	}
	else
	{
		m_spdX *= 0.97f;
	}

	if (m_keyFlg == (kA | kD))
	{
		m_dir.x = 0;
	}
}

void Player::UpdateMove1()
{
	m_keyFlg = None;

	// 出力
	if (GetAsyncKeyState(m_key[Throttle]) & 0x8000)
	{
		m_spd += 0.005f;

		m_keyFlg += Throttle;
	}
	if (GetAsyncKeyState(m_key[Brake]) & 0x8000)
	{
		m_spd -= 0.005f;

		m_keyFlg += Brake;
	}

	if (m_bSpeedLock)
	{
		// 最高速度
		if (m_spd >= 0.80f)
		{
			m_spd = 0.80f;
		}
		// 最低速度
		if (m_spd <= 0.030f)
		{
			m_spd = 0.030f;
		}
	}

	// ロール
	if (GetAsyncKeyState(m_key[RollLeft]) & 0x8000)
	{
		m_deg.z += 2.5f;
		if (m_deg.z > 360.0f)
		{
			m_deg.z = 0.0f;
		}
	}
	if (GetAsyncKeyState(m_key[RollRight]) & 0x8000)
	{
		m_deg.z -= 2.5f;
		if (m_deg.z < 0.0f)
		{
			m_deg.z = 360.0f;
		}
	}

	// ピッチ
	if (GetAsyncKeyState(m_key[PitchUp]) & 0x8000)
	{
		m_deg.x -= 2.5f;
		if (m_deg.x < 0.0f)
		{
			m_deg.x = 360.0f;
		}
	}
	if (GetAsyncKeyState(m_key[PitchDown]) & 0x8000)
	{
		m_deg.x += 2.5f;
		if (m_deg.x > 360.0f)
		{
			m_deg.x = 0.0f;
		}
	}

	// ヨー
	if (GetAsyncKeyState(m_key[YawLeft]) & 0x8000)
	{
		m_deg.y -= 0.8f;
		if (m_deg.y < 0.0f)
		{
			m_deg.y = 360.0f;
		}
	}
	if (GetAsyncKeyState(m_key[YawRight]) & 0x8000)
	{
		m_deg.y += 0.8f;
		if (m_deg.y > 360.0f)
		{
			m_deg.y = 0.0f;
		}
	}
}
