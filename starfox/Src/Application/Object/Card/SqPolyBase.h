#pragma once

class SqPolyBase : public KdGameObject
{
public:

	SqPolyBase();
	~SqPolyBase()		override;

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;

private:

	void Release();

protected:

	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;
	
	Math::Matrix						m_mTrans = Math::Matrix::Identity;


};