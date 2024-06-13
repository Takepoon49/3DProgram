#pragma once

class WeaponBase : public KdGameObject
{
public:
	WeaponBase();
	~WeaponBase() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

	virtual void OnHit() {};

	void UpdateMatrix();

private:

	void Release();

protected:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	float		  m_scale;
	Math::Vector3 m_pos;
	Math::Vector3 m_deg;

	Math::Matrix m_scaleMat;
	Math::Matrix m_rotXMat;
	Math::Matrix m_rotYMat;
	Math::Matrix m_rotZMat;
	Math::Matrix m_transMat;

};