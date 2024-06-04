#pragma once

#include"../BaseScene/BaseScene.h"

class PPlane;
class Heli;
class Seeker;
class Mouse;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	void ShotGLaser();

private:

	void Event() override;
	void Init() override;
	void ImGuiProcess() override;

	void MakeDonut(int _type);
	void MakeCube(Math::Vector3 _pos);

	void MakeWater(Math::Vector3 pos);

	void MakeSeeker();

	void CalcRad(Math::Vector3 _apos, Math::Vector3 _bpos, Math::Vector3* _rad);

	// 0.0～1.0の乱数取得
	float Rnd();

	// カメラ
	Math::Vector3	m_camPos = Math::Vector3::Zero;
	Math::Vector3	m_camRot = Math::Vector3::Zero;
	float			m_camFov = 60.0f;
	Math::Matrix	m_camMat = Math::Matrix::Identity;

	struct
	{
		Math::Vector3 pos;
		Math::Vector3 rot;
	}m_camType[2];
	int m_nowCamType;

	// プレイヤー
	std::weak_ptr<PPlane>	m_wpPlane;
	std::weak_ptr<Heli>		m_wpHeli;

	// 照準
	//std::weak_ptr<Seeker>	m_seeker;

	enum kFlg
	{
		k_c,
		k_space,
		k_end
	};

	bool m_keyFlg[k_end];
};