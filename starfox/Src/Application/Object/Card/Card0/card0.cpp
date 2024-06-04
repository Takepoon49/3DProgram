#include "card0.h"

void Card0::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	//m_spPoly->SetMaterial("Asset/Textures/img0/water.png");
	m_spPoly->SetMaterial("Asset/Textures/img0/runway.png");

	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//m_spPoly->SetScale({9.0f/2.0f, 12.0f/2.0f});
	//m_spPoly->SetScale({16.0f / 2.0f, 9.0f / 2.0f});
	m_spPoly->SetScale(100);

	m_pos = { 0.0f, 0.0f, -3.0f };
}

void Card0::Update()
{
	//m_pos.z -= 0.065f;
	//if (m_pos.z < -16.0f*2.0f) m_pos.z = -3.0f;

	Math::Matrix _RXMat =
		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));

	Math::Matrix _TMat =
		Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _RXMat * _TMat;

	//m_mWorld2 = _RXMat * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z + 16.0f * 4.0f);
	m_mWorld2 = _RXMat * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
}

void Card0::DrawLit()
//void Card1::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld2);
}
