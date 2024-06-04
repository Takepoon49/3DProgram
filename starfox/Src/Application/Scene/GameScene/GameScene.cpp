#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/pplane/pplane.h"		// 紙飛行機
#include "../../Object/terrain1/terrain1.h"	// 地形１

#include "../../Object/Heli/Heli.h"			// へり
#include "../../Object/Heli/Rotor/Rotor.h"	// ローター

#include "../../Object/Cube/cube.h"			// 箱

#include "../../Object/Card/Card0/card0.h"	// 板ポリ０
#include "../../Object/Card/Card1/card1.h"	// 板ポリ１

#include "../../Object/Donut/donut.h"		// ドーナツ１

#include "../../Object/GLaser/GLaser.h"		// 緑レーザー

#include "../../Object/Seeker/Seeker.h"		// レティクル

#include "../../Object/Stage/Water/Water.h"	// 水面

#include "../../main.h"

void GameScene::Event()
{
	Math::Matrix m_camPMat;

	if (m_wpHeli.expired() == false)
	{
		m_camPMat = 
			Math::Matrix::CreateTranslation(m_wpHeli.lock()->GetMatrix().Translation());
	}
	if (m_wpPlane.expired() == false)
	{
		m_camPMat =
			Math::Matrix::CreateTranslation(m_wpPlane.lock()->GetMatrix().Translation());
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

	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_nowCamType = 0;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_nowCamType = 1;
	}

	// カメラ更新
	//m_camPos = m_camType[m_nowCamType].pos;
	//m_camRot = m_camType[m_nowCamType].rot;

	m_camera->SetProjectionMatrix(m_camFov);

	Math::Matrix _camRXMat =
		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_camRot.x));
	Math::Matrix _camRYMat =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_camRot.y));
	Math::Matrix _camRZMat =
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_camRot.z));
	Math::Matrix _camTMat =
		Math::Matrix::CreateTranslation(m_camPos);

	m_camMat = (_camRXMat * _camRYMat * _camRZMat) * _camTMat;
	//m_camMat = (_camRXMat * _camRYMat * _camRZMat) * _camTMat * m_camPMat;
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

	// カメラ位置
	m_nowCamType = 0;

	//m_camType[0].pos = { 0.0f, 1.5f, -3.6f };
	//m_camType[0].rot = { 10.0f, 0.0f, 0.0f };

	m_camType[0].pos = { 0.0f, 3.5f, -5.0f };
	m_camType[0].rot = { 5.0f, 0.0f, 0.0f };

	m_camType[1].pos = { 0.0f, 4.5f, -4.6f };
	m_camType[1].rot = { 30.0f, 0.0f, 0.0f };

	m_camPos = m_camType[m_nowCamType].pos;
	m_camRot = m_camType[m_nowCamType].rot;

	// カメラ生成
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(m_camFov);
	m_camPos = m_camType[m_nowCamType].pos;
	m_camRot = m_camType[m_nowCamType].rot;
	Application::Instance().SetCamFov(&m_camFov);
	Application::Instance().SetCamPos(&m_camPos);
	Application::Instance().SetCamRot(&m_camRot);

	// 紙飛行機生成＆追加
	//std::shared_ptr<PPlane> _pplane;
	//_pplane = std::make_shared<PPlane>();
	//_pplane->Init();
	//m_objList.push_back(_pplane);
	//m_wpPlane = _pplane;

	// 本体追加
	//std::shared_ptr<Heli> heli;
	//heli = std::make_shared<Heli>();
	//heli->Init();
	//m_objList.push_back(heli);
	//m_wpHeli = heli;

	// ローター追加
	//std::shared_ptr<Rotor> rotor;
	//rotor = std::make_shared<Rotor>();
	//rotor->Init();
	//rotor->SetParentModel(heli);
	//m_objList.push_back(rotor);

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
	//MakeDonut(0);
	//MakeDonut(1);
	//MakeDonut(2);

	// 地面
	//std::shared_ptr<Card0> _card0;
	//_card0 = std::make_shared<Card0>();
	//_card0->Init();
	//m_objList.push_back(_card0);

	// 水面
	MakeWater({ 0, 0, 2 });

	// 背景の空
	//std::shared_ptr<Card1> _card1;
	//_card1 = std::make_shared<Card1>();
	//_card1->Init();
	//_card1->SetCamMat(&m_camMat);
	//m_objList.push_back(_card1);
}

void GameScene::ImGuiProcess()
{
	//return;

//========================================================================
// ImGui開始
//========================================================================
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//========================================================================
	// ImGui 描画処理
	//========================================================================

	// ImGui Demo ウィンドウ表示 ※すごく参考になるウィンドウです。imgui_demo.cpp参照。
	//ImGui::ShowDemoWindow(nullptr);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		POINT mousePos;
		GetCursorPos(&mousePos);

		float* camPos[3] = { &m_camPos.x, &m_camPos.y, &m_camPos.z };
		float* camRot[3] = { &m_camRot.x, &m_camRot.y, &m_camRot.z };

		ImGui::Text("%d, %d", mousePos.x, mousePos.y);
		ImGui::Text("%d, %d", (int)mousePos.x - 640, (int)mousePos.y - 360);
		ImGui::DragFloat("Fov", &m_camFov, 1.0f, 1.0f, 360.0f, "%.3f");
		ImGui::DragFloat3("Pos", *camPos, 0.05f, -100.0f, +100.0f, "%.3f");
		ImGui::DragFloat3("Rot", *camRot, 0.05f, -100.0f, +100.0f, "%.3f");

		if (m_wpHeli.expired() == false)
		{
			Math::Vector3 heliRot = m_wpHeli.lock()->GetRot();
			Math::Vector3 heliSpd = m_wpHeli.lock()->GetSpd();
			Math::Vector3 heliVec = m_wpHeli.lock()->GetVec();

			ImGui::Text("Heli.Rot:(%.3f, %.3f, %.3f)", heliRot.x, heliRot.y, heliRot.z);
			ImGui::Text("Heli.Spd:(%.3f, %.3f, %.3f)", heliSpd.x, heliSpd.y, heliSpd.z);
			ImGui::Text("Heli.Vec:(%.3f, %.3f, %.3f)", heliVec.x, heliVec.y, heliVec.z);
		}

	}
	ImGui::End();

	//========================================================================
	// ImGuiのレンダリング : ここより上にimguiの描画はすること
	//========================================================================
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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

void GameScene::MakeWater(Math::Vector3 pos)
{
	std::shared_ptr<Water> water;
	water = std::make_shared<Water>();
	water->Init(pos);
	m_objList.push_back(water);
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
	if (m_wpPlane.expired() == false)
	{
		//if (m_seeker.expired() == false)
		{
			// 始点
			Math::Vector3 ppos = m_wpPlane.lock()->GetPos();
			// 終点
			Math::Vector3 bpos = { ppos.x, ppos.y, 30.0f };
			//Math::Vector3 bpos = { 0.0f, 0.0f, 30.0f };
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