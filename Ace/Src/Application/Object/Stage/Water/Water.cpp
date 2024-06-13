#include "Water.h"

Water::Water()
{
	//m_count = 0;
	//m_anim = 0;
}

Water::~Water()
{

}

void Water::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Stage/Sea/Sea.gltf");

	m_mWorld = Math::Matrix::CreateScale(200.0f);
	m_mWorld *= Math::Matrix::CreateTranslation(0.0f, -1.5f, 0.0f);
}

void Water::Update()
{
	//m_count++;
	//if (m_count >= 10)
	//{
	//	m_count = 0;

	//	m_anim++;
	//	if (m_anim > 3)
	//	{
	//		m_anim = 0;
	//	}
	//}

	//m_spPoly->SetUVRect(m_anim);
}