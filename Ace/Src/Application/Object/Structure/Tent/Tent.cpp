#include "Tent.h"

Tent::Tent()
{

}

Tent::~Tent()
{

}

void Tent::Init()
{
	StructBase::Init();

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/GroundTGT/Tent/Tent.gltf");
}

void Tent::Update()
{

}

void Tent::OnHit()
{

}
