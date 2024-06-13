#pragma once

class AfterBurner : public KdGameObject
{
public: 

	AfterBurner();
	~AfterBurner() override;

	void Init() override;
	void Update() override;
	void DrawBright() override;

	void SetPair(std::shared_ptr<KdGameObject> obj)
	{
		m_pair = obj;
	}

private:

	std::shared_ptr<KdGameObject> m_pair = nullptr;

	std::shared_ptr<KdModelData> m_spModel = nullptr;

};