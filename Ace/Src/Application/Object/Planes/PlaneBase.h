#pragma once

class PlaneBase : public KdGameObject
{
public:

	PlaneBase();
	~PlaneBase() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

private:

	void Release();

protected:

	std::shared_ptr<KdModelData> m_spModel;

};