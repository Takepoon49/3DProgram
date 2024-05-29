#include "Seeker.h"
#include "../../main.h"

void Seeker::Init()
{
	m_tex.Load("Asset/Textures/img0/seeker.png");

	m_pos = Math::Vector3(0.0f, 0.0f, 0.0f);
	m_deg = 0.0f;
	m_mousePos = { 0, 0 };
	m_bMouse = true;
}

void Seeker::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		if (!m_keyFlg[k_p])
		{
			m_bMouse = !m_bMouse;
		}
		m_keyFlg[k_p] = true;
	}
	else
	{
		m_keyFlg[k_p] = false;
	}

	if (m_bMouse)
	{
		GetMousePos2(&m_mousePos);
		//SetMousePos2(640, 360);
	}

	// 移動処理
	m_pos.x = (int)m_mousePos.x;
	m_pos.y = (int)m_mousePos.y;

	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	m_pos.y += 6.0f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_pos.y -= 6.0f;
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//	m_pos.x -= 6.0f;
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//	m_pos.x += 6.0f;
	//}

	// 回転処理
	if (GetAsyncKeyState('5') & 0x8000)
	{
		m_deg += 1.0f;
	}
	if (GetAsyncKeyState('6') & 0x8000)
	{
		m_deg -= 1.0f;
	}
	if (m_deg >= 360.0f) m_deg -= 360.0f;

	// 行列更新
	Math::Matrix sMat =
		Math::Matrix::CreateScale(0.8f);
	Math::Matrix rMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	Math::Matrix tMat =
		Math::Matrix::CreateTranslation(m_pos);
	
	// 行列合成
	m_mWorld = sMat * rMat * tMat;

	sMat = Math::Matrix::CreateScale(0.5f);
	rMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	tMat = Math::Matrix::CreateTranslation(m_pos);

	m_farMat = sMat * rMat * tMat;
}

void Seeker::DrawSprite()
{
	Math::Color color = Math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	Math::Rectangle rect = Math::Rectangle(0, 0, 100, 100);

	// 遠いほう
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_farMat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);

	//color = Math::Color(0.0f, 1.0f, 0.0f, 1.0f);

	// 近いほう
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);

	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void Seeker::GetMousePos2(POINT* apMousePos)
{
	GetCursorPos(apMousePos);

	ScreenToClient(Application::Instance().GetWindowHandle(), apMousePos);

	apMousePos->x -= 1280.0f / 2.0f;
	apMousePos->y -= 720.0f / 2.0f;
	apMousePos->y *= -1;
}

void Seeker::SetMousePos2(int x, int y)
{
	POINT mousePos = { x, y };

	ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);

	SetCursorPos((int)mousePos.x, (int)mousePos.y);
}