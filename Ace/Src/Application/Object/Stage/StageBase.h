#pragma once

class StageBase : public KdGameObject
{
public:

	StageBase();
	~StageBase()	override;

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

	void SetPlayerSpeed(float* speed) { m_playerSpeed = speed; }

private:

	void Release();

protected:

	std::shared_ptr<KdModelData>	m_spModel = nullptr;
	Math::Vector3					m_scale = Math::Vector3::One;

	float* m_playerSpeed;
};