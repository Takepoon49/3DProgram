#include "StructA.h"

StructA::StructA()
{

}

StructA::~StructA()
{
	Release();
}

void StructA::Init()
{
	StructBase::Init();

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/GroundTGT/HouseA/HouseA.gltf");
}

void StructA::OnHit()
{
	m_isExpired = true;
}

void StructA::Release()
{
	m_spModel = nullptr;
}
