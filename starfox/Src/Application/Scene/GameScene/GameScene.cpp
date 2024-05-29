#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/pplane/pplane.h"		// 紙飛行機
#include "../../Object/terrain1/terrain1.h"	// 地形１

#include "../../Object/Heli/Heli.h"			// へり

#include "../../Object/Cube/cube.h"			// 箱

#include "../../Object/Card/Card0/card0.h"	// 板ポリ０
#include "../../Object/Card/Card1/card1.h"	// 板ポリ１

#include "../../Object/Donut/donut.h"		// ドーナツ１

#include "../../Object/GLaser/GLaser.h"		// 緑レーザー

#include "../../Object/Seeker/Seeker.h"		// レティクル

#include "../../main.h"

void GameScene::Event()
{
	Math::Matrix m_pplaneMat;

	if (m_pplane.expired() == false)
	{
		Application::Instance().SetTestInt1(m_pplane.lock()->GetInt());
		Application::Instance().SetTestFloat1(m_pplane.lock()->GetFloat());
 
		m_pplaneMat = Math::Matrix::CreateTranslation(m_pplane.lock()->GetMatrix().Translation());
	}

	// スペースで弾発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_keyFlg[k_space])
		{
			ShotGLaser();
		}
		m_keyFlg[k_space] = true;
	}
	else
	{
		m_keyFlg[k_space] = false;
	}

	if (GetAsyncKeyState(VK_NUMPAD9))	m_camPos.y += 0.05f;
	if (GetAsyncKeyState(VK_NUMPAD3))	m_camPos.y -= 0.05f;

	if (GetAsyncKeyState(VK_NUMPAD7))	m_camPos.z += 0.05f;
	if (GetAsyncKeyState(VK_NUMPAD1))	m_camPos.z -= 0.05f;

	if (GetAsyncKeyState(VK_NUMPAD8))	m_camRot.x -= 1.0f;
	if (GetAsyncKeyState(VK_NUMPAD2))	m_camRot.x += 1.0f;
	if (GetAsyncKeyState(VK_NUMPAD4))	m_camRot.y -= 1.0f;
	if (GetAsyncKeyState(VK_NUMPAD6))	m_camRot.y += 1.0f;

	// カメラ更新
	m_camera->SetProjectionMatrix(m_camFov);

	Math::Matrix _camRXMat =
		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_camRot.x));
	Math::Matrix _camRYMat =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_camRot.y));
	Math::Matrix _camRZMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_camRot.z));
	Math::Matrix _camTMat =
		Math::Matrix::CreateTranslation(m_camPos);

	m_camMat = (_camRXMat * _camRYMat * _camRZMat) * _camTMat * m_pplaneMat;
	m_camera->SetCameraMatrix(m_camMat);

	// Cキーでキューブ追加
	if (GetAsyncKeyState('C') & 0x8000)
	{
		if (!m_keyFlg[k_c])
		{
			// キューブ
			MakeCube({ Rnd() * 20.0f - 10.0f, 0.0f, 30.0f });
		}
		m_keyFlg[k_c] = true;
	}
	else
	{
		m_keyFlg[k_c] = false;
	}

	// Tキーでタイトルに遷移
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0, -1, 1 }, { 3, 3, 3 });

	srand(timeGetTime());

	// キーフラグ初期化
	for (auto& flg : m_keyFlg)
	{
		flg = false;
	}

	// カメラ生成
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(m_camFov);
	m_camPos = { 0.0f, 1.5f, -3.6f };
	m_camRot = { 15.0f, 0.0f, 0.0f };
	Application::Instance().SetCamFov(&m_camFov);
	Application::Instance().SetCamPos(&m_camPos);
	Application::Instance().SetCamRot(&m_camRot);

	// 紙飛行機生成＆追加
	std::shared_ptr<PPlane> _pplane;
	_pplane = std::make_shared<PPlane>();
	_pplane->Init();
	m_objList.push_back(_pplane);
	m_pplane = _pplane;

	// ローター追加
	std::shared_ptr<Heli> heli;
	heli = std::make_shared<Heli>();
	heli->Init();
	m_objList.push_back(heli);

	// オブジェクト
	//std::shared_ptr<Terrain1> _terrain1;
	//_terrain1 = std::make_shared<Terrain1>();
	//_terrain1->Init();
	//m_objList.push_back(_terrain1);

	// キューブ
	//MakeCube({ -6.0f, 0.0f, 30.0f });
	//MakeCube({  0.0f, 0.0f, 30.0f });
	//MakeCube({ +6.0f, 0.0f, 30.0f });

	// ドーナツ
	MakeDonut(0);
	MakeDonut(1);
	MakeDonut(2);

	// 地面
	std::shared_ptr<Card0> _card0;
	_card0 = std::make_shared<Card0>();
	_card0->Init();
	m_objList.push_back(_card0);

	// 背景の空
	std::shared_ptr<Card1> _card1;
	_card1 = std::make_shared<Card1>();
	_card1->Init();
	_card1->SetCamMat(&m_camMat);
	m_objList.push_back(_card1);
}

void GameScene::MakeDonut(int _type)
{
	std::shared_ptr<Donut> _donut;
	_donut = std::make_shared<Donut>(_type);
	_donut->Init();
	m_objList.push_back(_donut);
}

void GameScene::MakeCube(Math::Vector3 _pos)
{
	std::shared_ptr<Cube> cube;
	cube = std::make_shared<Cube>();
	cube->Init(_pos);
	m_objList.push_back(cube);
}

void GameScene::MakeSeeker()
{
	// レティクル
	std::shared_ptr<Seeker> _seeker;
	_seeker = std::make_shared<Seeker>();
	_seeker->Init();
	m_objList.push_back(_seeker);
	//m_seeker = _seeker;
}

void GameScene::CalcRad(Math::Vector3 _apos, Math::Vector3 _bpos, Math::Vector3* _rad)
{
	Math::Vector3 c_pos;
	c_pos.x = _bpos.x - _apos.x;
	c_pos.y = _bpos.y - _apos.y;
	float radianY = atan2(c_pos.y, c_pos.x);
	_rad->y = radianY;

	c_pos.x = _bpos.z - _apos.z;
	c_pos.y = _bpos.y - _apos.y;
	float radianX = atan2(c_pos.y, c_pos.z);
	_rad->x = radianX;

	//_move->x = cos(radianY) * 0.35f;
	//_move->y = sin(radianY) * 0.35f;
	//_move->z = cos(radianX) * 0.35f;
}

float GameScene::Rnd()
{
	return rand() / (float)RAND_MAX;
}

void GameScene::ShotGLaser()
{
	if (m_pplane.expired() == false)
	{
		//if (m_seeker.expired() == false)
		{
			// 始点
			Math::Vector3 ppos = m_pplane.lock()->GetPos();
			// 終点
			//Math::Vector3 bpos = { ppos.x, ppos.y, 30.0f };
			Math::Vector3 bpos = { 0.0f, 0.0f, 30.0f };
			// 移動量
			Math::Vector3 moveVec = bpos - ppos;
			moveVec.Normalize();
			moveVec *= 0.35f;

			// 角度
			Math::Vector3 rad;
			//rad.x = -atan2(moveVec.y, moveVec.z);
			//rad.y = -atan2(moveVec.z, moveVec.x);
			//rad.z = 0.0f;
			rad = Math::Vector3::Zero;

			// 緑レーザー
			std::shared_ptr<GLaser> _gLaser;
			_gLaser = std::make_shared<GLaser>();
			_gLaser->Init(ppos, moveVec, rad);
			m_objList.push_back(_gLaser);
		}
	}
}