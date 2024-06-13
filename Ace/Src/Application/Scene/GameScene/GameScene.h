#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class PPlane;
class Heli;
class Seeker;
//class Sound;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	void ShotGLaser();

private:

	void OldEvent();

	void Event() override;
	void Init() override;
	void ImGuiProcess() override;

	void MakeDonut(int _type);

	void MakeSeeker();

	void CalcRad(Math::Vector3 _apos, Math::Vector3 _bpos, Math::Vector3* _rad);

	// 建物のデータ読み込み
	enum
	{
		stType,
		stPosX,
		stPosY,
		stPosZ,
		stRotX,
		stRotY,
		stRotZ,
		stScale
	};
	enum
	{
		stBox,
		stTent
	};
	void LoadStructData();
	void MakeStructA(Math::Vector3 _pos, Math::Vector3 _rot, float _scale);
	void MakeTent(Math::Vector3 _pos, Math::Vector3 _rot, float _scale);

	// 数字かどうか
	bool isInt(std::string s);

	// 0.0～1.0の乱数取得
	float Rnd();

	// カメラ
	int				m_nowCamPos = 0;
	Math::Vector3	m_camPos = {};
	Math::Vector3	m_camRot = {};
	float			m_camFov = 60.0f;
	Math::Matrix	m_camMat = Math::Matrix::Identity;
	bool			m_bFollowPlayer;

	//struct
	//{
	//	Math::Vector3 pos;
	//	Math::Vector3 rot;
	//}m_camType[2];
	//int m_nowCamType;

	// プレイヤー
	std::weak_ptr<Player> m_wpPlayer;
	float* m_playerSpeed;

	std::weak_ptr<PPlane>	m_wpPlane;
	std::weak_ptr<Heli>		m_wpHeli;

	// サウンド
	//std::weak_ptr<Sound>	m_wpSound;

	// 照準
	std::weak_ptr<Seeker>	m_wpSeeker;

	enum kFlg
	{
		k_p,
		k_c,
		k_space,
		k_end
	};

	bool m_keyFlg[k_end];
};