#pragma once

class Rotor : public KdGameObject
{
public:

	Rotor();
	~Rotor() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;

	void SetParentModel(const std::shared_ptr<KdGameObject> parent)
	{
		m_wpParent = parent;
	}

private:

	std::shared_ptr<KdModelData> m_spModel;
	std::weak_ptr<KdGameObject> m_wpParent;
	Math::Matrix m_mPare;

	Math::Vector3 m_pos;
	Math::Vector3 m_angle;

	Math::Matrix m_mScale;
	Math::Matrix m_mRotX;
	Math::Matrix m_mRotY;
	Math::Matrix m_mRotZ;
	Math::Matrix m_mTrans;

};