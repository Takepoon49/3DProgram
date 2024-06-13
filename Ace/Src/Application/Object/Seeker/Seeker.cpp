#include "Seeker.h"

void Seeker::Init()
{
	m_tex.Load("Asset/Textures/img0/seeker.png");

	m_pos = Math::Vector3(0.0f, 0.0f, 0.0f);
	m_pos = Math::Vector3(0.0f, 0.0f, 0.0f);
	m_deg = 0.0f;
	m_scale = 0.8f;
}

void Seeker::Update()
{
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
		Math::Matrix::CreateScale(m_scale);
	Math::Matrix rMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	Math::Matrix tMat =
		Math::Matrix::CreateTranslation(m_pos);
	
	// 行列合成
	m_mWorld = sMat * rMat * tMat;

	sMat = Math::Matrix::CreateScale(m_scale/2.0f);
	rMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	tMat = Math::Matrix::CreateTranslation(m_farPos);

	m_farMat = sMat * rMat * tMat;
}

void Seeker::DrawSprite()
{
	Math::Color color = Math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	Math::Rectangle rect = Math::Rectangle(0, 0, 100, 100);

	// 遠いほう
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_farMat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);

	color = Math::Color(0.0f, 1.0f, 0.0f, 1.0f);

	// 近いほう
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);

	// これやらないと全部動く
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}