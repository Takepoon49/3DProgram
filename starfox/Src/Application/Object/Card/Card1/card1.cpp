#include "card1.h"

void Card1::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Textures/img0/sky.png");
	//m_spPoly->SetMaterial("Asset/Textures/img1/ndsk.png");
	//m_spPoly->SetMaterial("Asset/Textures/img1/ysn.png");
	//m_spPoly->SetMaterial("Asset/Textures/img1/mr.png");

	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Middle);

	//m_spPoly->SetScale({9.0f/2.0f, 12.0f/2.0f});
	//m_spPoly->SetScale({16.0f / 2.0f, 9.0f / 2.0f});
	m_spPoly->SetScale({16.0f * 7.0f, 9.0f * 7.0f});
}

void Card1::Update()
{
	Math::Matrix _TMat =
		Math::Matrix::CreateTranslation(0.0f, 0.0f, 50.0f);

	m_mWorld = _TMat * (*m_camMat);
}

void Card1::DrawLit()
//void Card1::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
