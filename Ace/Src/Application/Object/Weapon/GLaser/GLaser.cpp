#include "GLaser.h"
#include "../../pplane/pplane.h"

void GLaser::Init(Math::Vector3 pos, Math::Matrix mat, Math::Vector3 _move, Math::Vector3 _rad)
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/GLaser/laser.gltf");

	m_pos = pos;
	m_move = _move;
	m_rad = _rad;

	UpdateMatrix();
}

void GLaser::Update()
{
	//m_pos.z += 0.35f;
	m_pos += m_move;
	if (m_pos.z > +100.0f)
	{
		m_isExpired = true;
		//Math::Vector3 pairPos = m_pair->GetPos();
		//m_pos.x = pairPos.x;
		//m_pos.y = pairPos.y;
		//m_pos.z = pairPos.z + 1.0f;
	}

	//m_rad.x += DirectX::XMConvertToRadians(30.0f);
	//m_rad.y += DirectX::XMConvertToRadians(30.0f);

	UpdateMatrix();
}

void GLaser::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void GLaser::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void GLaser::UpdateMatrix()
{
	m_rotXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rad.x));
	m_rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rad.y));
	m_rotZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rad.z));
	m_TMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotXMat * m_rotYMat * m_rotZMat * m_TMat;
}
