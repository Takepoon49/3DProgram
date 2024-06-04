#include "Water.h"

Water::Water()
{
	m_count = 0;
	m_anim = 0;
}

Water::~Water()
{

}

void Water::Init(Math::Vector3 pos)
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Textures/Stage/Water/Water64x4.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Right_Top);

	Math::Matrix transMat =
		Math::Matrix::CreateTranslation(pos);

	m_spPoly->SetScale(1.0f);

	m_spPoly->SetSplit(4, 1);

	m_mWorld = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));
	m_mWorld *= transMat;
}

void Water::Update()
{
	m_count++;
	if (m_count >= 10)
	{
		m_count = 0;

		m_anim++;
		if (m_anim > 3)
		{
			m_anim = 0;
		}
	}

	m_spPoly->SetUVRect(m_anim);
}

void Water::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
