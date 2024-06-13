#pragma once

class StructBase : public KdGameObject
{
public:

	StructBase();
	~StructBase() override;

	void Init();
	void Update() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

	void SetParameter(Math::Vector3 pos, Math::Vector3 rot, float scale);

private:

	void Release();

protected:

	std::shared_ptr<KdModelData> m_spModel;

};