#include "Bomb.h"

Bomb::Bomb()
{

}

Bomb::~Bomb()
{

}

void Bomb::Init()
{
	WeaponBase::Init();

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Weapon/Bomb/Bomb.gltf");

	UpdateMatrix();
}

void Bomb::Update()
{
	UpdateMatrix();
}

void Bomb::OnHit()
{

}

void Bomb::SetMatrix(Math::Matrix matrix)
{
	m_mWorld = matrix;
}
