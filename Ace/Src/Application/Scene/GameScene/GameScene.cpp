#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/pplane/pplane.h"			// 紙飛行機
#include "../../Object/terrain1/terrain1.h"		// 地形１


#include "../../Object/Planes/Player/Player.h"	// プレイヤー
#include "../../Object/Heli/Heli.h"				// へり
#include "../../Object/Heli/Rotor/Rotor.h"		// ローター

#include "../../Object/Stage/Donut/donut.h"			// ドーナツ１

#include "../../Object/Weapon/GLaser/GLaser.h"	// 緑レーザー

#include "../../Object/Seeker/Seeker.h"			// レティクル

#include "../../Object/Stage/Water/Water.h"		// 水面

#include "../../Object/Stage/Desert/Desert.h"	// 砂漠

//#include "../../Object/Sound/Sound.h"			// サウンド

// Structure
#include "../../Object/Structure/StructA/StructA.h"	// 箱
#include "../../Object/Structure/Tent/Tent.h"		// テント

#include "../../main.h"

void GameScene::OldEvent()
{
	Math::Matrix m_camPMat;
	Math::Vector3 pplanePos = {};

	//if (m_wpHeli.expired() == false)
	//{
	//	m_camPMat = 
	//		Math::Matrix::CreateTranslation(m_wpHeli.lock()->GetMatrix().Translation());
	//}
	std::shared_ptr<PPlane> pplane = m_wpPlane.lock();
	if (pplane)
	{
		m_camPMat =
			Math::Matrix::CreateTranslation(m_wpPlane.lock()->GetMatrix().Translation());

		pplanePos = pplane->GetPos();

		std::shared_ptr<Seeker> seeker = m_wpSeeker.lock();
		if (seeker)
		{
			//m_camera->ConvertWorldToScreenDetail(pplane->GetSeekerPos(), *seeker->GetPosA());

			Math::Vector3 seekerPos = {};
			// 近いほう
			m_camera->ConvertWorldToScreenDetail(pplane->GetSeekerPos(0), seekerPos);
			seekerPos.z = 0.0f;
			seeker->SetPos(seekerPos);
			// 遠いほう
			m_camera->ConvertWorldToScreenDetail(pplane->GetSeekerPos(1), seekerPos);
			seekerPos.z = 0.0f;
			seeker->SetFarPos(seekerPos);
		}
	}

	// スペースで弾発射
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//{
	//	if (!m_keyFlg[k_space])
	//	{
	//		ShotGLaser();
	//	}
	//	m_keyFlg[k_space] = true;
	//}
	//else
	//{
	//	m_keyFlg[k_space] = false;
	//}

	//if (GetAsyncKeyState('1') & 0x8000)
	//{
	//	m_nowCamType = 0;
	//}
	//if (GetAsyncKeyState('2') & 0x8000)
	//{
	//	m_nowCamType = 1;
	//}

	//m_camPos = m_camType[m_nowCamType].pos;
	//m_camRot = m_camType[m_nowCamType].rot;

	// カメラワーク
	//m_camPos.x = pplanePos.x;
	//if (m_camPos.x < -3.0f)
	//{
	//	m_camPos.x = -3.0f;
	//}
	//if (m_camPos.x > 3.0f)
	//{
	//	m_camPos.x = +3.0f;
	//}
}

void GameScene::Event()
{
	// カメラをプレイヤーに追従
	if (GetAsyncKeyState('P') & 0x8000)
	{
		if (!m_keyFlg[k_p])
		{
			m_keyFlg[k_p] = true;

			m_bFollowPlayer = !m_bFollowPlayer;
		}
	}
	else
	{
		m_keyFlg[k_p] = false;
	}

	Math::Matrix playerMat;
	// プレイヤーに追従するかどうか
	if (m_bFollowPlayer)
	{
		// カメラ切り替え
		if (GetAsyncKeyState('C') & 0x8000)
		{
			if (!m_keyFlg[k_c])
			{
				m_nowCamPos++;
				if (m_nowCamPos > 2)
				{
					m_nowCamPos = 0;
				}
			}
			m_keyFlg[k_c] = true;
		}
		else
		{
			m_keyFlg[k_c] = false;
		}
		switch (m_nowCamPos)
		{
		case 0:
			m_camPos = { 0.0f, 1.1f, -3.6f };
			m_camRot = { 0.0f, 0.0f, 0.0f };
			break;

		case 1:
			m_camPos = { 0.0f, 8.5f, 0.0f };
			m_camRot = { 75.0f, 0.0f, 0.0f };
			break;

		case 2:
			m_camPos = { 0.0f, 6.0f, -8.0f };
			m_camRot = { 25.0f, 0.0f, 0.0f };
			break;
		}

		std::shared_ptr<Player> player = m_wpPlayer.lock();
		if (player)
		{
			//m_camPos = player->GetPos();
			//playerMat = Math::Matrix::CreateTranslation(player->GetMatrix().Translation());
			playerMat = player->GetMatrix();
		}
	}
	else
	{
		// カメラ操作
		if (GetAsyncKeyState(VK_NUMPAD9))	m_camPos.y += 0.05f;
		if (GetAsyncKeyState(VK_NUMPAD3))	m_camPos.y -= 0.05f;

		if (GetAsyncKeyState(VK_NUMPAD7))	m_camPos.z += 0.05f;
		if (GetAsyncKeyState(VK_NUMPAD1))	m_camPos.z -= 0.05f;

		if (GetAsyncKeyState(VK_NUMPAD8))	m_camRot.x -= 1.0f;
		if (GetAsyncKeyState(VK_NUMPAD2))	m_camRot.x += 1.0f;
		if (GetAsyncKeyState(VK_NUMPAD4))	m_camRot.y -= 1.0f;
		if (GetAsyncKeyState(VK_NUMPAD6))	m_camRot.y += 1.0f;

		if (GetAsyncKeyState('W') & 0x8000) m_camPos.z += 0.05f;
		if (GetAsyncKeyState('S') & 0x8000) m_camPos.z -= 0.05f;
		if (GetAsyncKeyState('A') & 0x8000) m_camPos.x -= 0.05f;
		if (GetAsyncKeyState('D') & 0x8000) m_camPos.x += 0.05f;
	}

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

	if (m_bFollowPlayer)
	{
		m_camMat = (_camRXMat * _camRYMat * _camRZMat) * _camTMat * playerMat;
	}
	else
	{
		m_camMat = (_camRXMat * _camRYMat * _camRZMat) * _camTMat;
	}
	m_camera->SetCameraMatrix(m_camMat);

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
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0, -1, -1 }, { 3, 3, 3 });

	srand(timeGetTime());

	// サウンド
	//std::shared_ptr<Sound> sound;
	//sound = std::make_shared<Sound>();
	//sound->Init();
	//m_wpSound = sound;
	//sound->GetBGMInst(BGM_test)->Play();

	// キーフラグ初期化
	for (auto& flg : m_keyFlg)
	{
		flg = false;
	}

	// カメラをプレイヤーに追従
	m_bFollowPlayer = true;

	// カメラ位置
	m_nowCamPos = 0;

	// カメラ生成
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(m_camFov);
	//m_camPos = m_camType[m_nowCamType].pos;
	//m_camRot = m_camType[m_nowCamType].rot;
	//Application::Instance().SetCamFov(&m_camFov);
	//Application::Instance().SetCamPos(&m_camPos);
	//Application::Instance().SetCamRot(&m_camRot);

	// 紙飛行機生成＆追加
	//std::shared_ptr<PPlane> _pplane;
	//_pplane = std::make_shared<PPlane>();
	//_pplane->Init();
	//m_objList.push_back(_pplane);
	//m_wpPlane = _pplane;

	// シーカー
	//MakeSeeker();

	// プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);
	m_wpPlayer = player;
	m_playerSpeed = player->GetSpdA();

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
	//MakeCube({ 0.0f, -3.0f, 0.0f });
	//MakeCube({  0.0f, 0.0f, 30.0f });
	//MakeCube({ +6.0f, 0.0f, 30.0f });

	// ドーナツ
	MakeDonut(0);
	MakeDonut(1);
	MakeDonut(2);

	// 地面
	//std::shared_ptr<Card0> _card0;
	//_card0 = std::make_shared<Card0>();
	//_card0->Init();
	//m_objList.push_back(_card0);

	// 水面
	//MakeWater({ 0, 0, 2 });

	// StructA
	//Math::Vector3 stPos = { 3, 0, 3 };
	//Math::Vector3 stRot = { 0, 0, 0 };
	//MakeStructA(stPos, stRot);

	// ファイル読み込み
	LoadStructData();

	// 海面
	std::shared_ptr<Water> water;
	water = std::make_shared<Water>();
	water->Init();
	m_objList.push_back(water);

	// 砂漠
	std::shared_ptr<Desert> desert;
	desert = std::make_shared<Desert>();
	desert->Init();
	desert->SetPlayerSpeed(m_playerSpeed);
	m_objList.push_back(desert);

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
		ImGui::Checkbox("FollowPlayer", &m_bFollowPlayer);

		POINT mousePos;
		GetCursorPos(&mousePos);

		float* camPos[3] = { &m_camPos.x, &m_camPos.y, &m_camPos.z};
		float* camRot[3] = { &m_camRot.x, &m_camRot.y, &m_camRot.z};

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
		if (m_wpPlane.expired() == false)
		{
			Math::Vector3 planePos;
			planePos = m_wpPlane.lock()->GetPos();
			ImGui::Text("Player: %.1f, %.1f, %.1f", planePos.x, planePos.y, planePos.y);
		}

		if (m_wpSeeker.expired() == false)
		{
			Math::Vector3 seekerPos;
			seekerPos = m_wpSeeker.lock()->GetPos();
			ImGui::Text("SeekerPos: %.1f, %.1f, %.1f", seekerPos.x, seekerPos.y, seekerPos.y);
		}

		if (m_wpPlayer.expired() == false)
		{
			float speed = m_wpPlayer.lock()->GetSpd();
			ImGui::Text("PlayerSpd: %.8f", speed);
			speed = m_wpPlayer.lock()->GetSpdX();
			ImGui::Text("PlayerSpdX: %.8f", speed);

			Math::Vector3 dir = m_wpPlayer.lock()->GetDir();
			ImGui::Text("PlayerDir: %.2f, %.2f, %.2f", dir.x, dir.y, dir.z);

			Math::Vector3 pos = m_wpPlayer.lock()->GetPos();
			ImGui::Text("PlayerPos: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);

			Math::Vector3 deg = m_wpPlayer.lock()->GetDeg();
			ImGui::Text("PlayerDeg: %.2f, %.2f, %.2f", deg.x + 90.0f, deg.y, deg.z + 90.0f);
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
	_donut->SetPlayerSpeed(m_playerSpeed);
	m_objList.push_back(_donut);
}

void GameScene::MakeStructA(Math::Vector3 _pos, Math::Vector3 _rot, float _scale)
{
	std::shared_ptr<StructA> obj;
	obj = std::make_shared<StructA>();
	obj->Init();
	obj->SetParameter(_pos, _rot, _scale);
	m_objList.push_back(obj);
}

void GameScene::MakeTent(Math::Vector3 _pos, Math::Vector3 _rot, float _scale)
{
	std::shared_ptr<Tent> obj;
	obj = std::make_shared<Tent>();
	obj->Init();
	obj->SetParameter(_pos, _rot, _scale);
	m_objList.push_back(obj);
}

void GameScene::MakeSeeker()
{
	// レティクル
	std::shared_ptr<Seeker> _seeker;
	_seeker = std::make_shared<Seeker>();
	_seeker->Init();
	m_objList.push_back(_seeker);
	m_wpSeeker = _seeker;
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

void GameScene::LoadStructData()
{
	std::ifstream ifs("Asset/Data/StructData.csv");

	std::string str, field;

	int h = 0;
	int w = 0;

	UINT type = 0;
	Math::Vector3 pos = {};
	Math::Vector3 rot = {};
	float scale = {};

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		while (getline(iss, field, ','))
		{
			if (isInt(field) == false)	// セルに文字列が含まれていた場合
			{
				
			}
			else // セルが数字だけの場合
			{
				switch (w)
				{
				case stType:
					type = stof(field);
					break;

				case stPosX:
					pos.x = stof(field);
					break;
				
				case stPosY:
					pos.y = stof(field);
					break;
				
				case stPosZ:
					pos.z = stof(field);
					break;
				
				case stRotX:
					rot.x = stof(field);
					break;
				
				case stRotY:
					rot.y = stof(field);
					break;
				
				case stRotZ:
					rot.z = stof(field);
					break;
				
				case stScale:
					scale = stof(field);
					break;
				}
			}
			w++;	// 次の列へ
		}
		w = 0;	// 列をリセット
		h++;	// 次の行へ

		switch (type)
		{
		case stBox:
			MakeStructA(pos, rot, scale);
			break;

		case stTent:
			MakeTent(pos, rot, scale);
			break;
		}

		pos = {};
		rot = {};
	}

	ifs.close();
}

bool GameScene::isInt(std::string s)
{
	for (const char& c : s)
	{
		if (c == '-') continue;	// マイナスをスキップ

		if (isdigit(c) == 0)	// 文字に数字以外があったら
		{
			return false;
		}
	}

	return true;
}

float GameScene::Rnd()
{
	return rand() / (float)RAND_MAX;
}

void GameScene::ShotGLaser()
{
	std::shared_ptr<PPlane> plane = m_wpPlane.lock();
	if (plane)
	{
		//if (m_seeker.expired() == false)
		{
			// 始点
			Math::Vector3 ppos = plane->GetPos() + Math::Vector3(0.0f, 0.0f, 2.0f);
			Math::Matrix matrix = plane->GetMatrix();
			// 終点
			Math::Vector3 bpos = { ppos.x, ppos.y, 30.0f };
			//Math::Vector3 bpos = { 0.0f, 0.0f, 30.0f };
			// 移動量
			//Math::Vector3 moveVec = bpos - ppos;

			Math::Vector3 moveVec = plane->GetDir();

			moveVec.Normalize();
			moveVec *= 1.5f;

			// 角度
			Math::Vector3 rot;
			rot = plane->GetRot();

			// 緑レーザー
			std::shared_ptr<GLaser> _gLaser;
			_gLaser = std::make_shared<GLaser>();
			_gLaser->Init(ppos, matrix, moveVec, rot);
			m_objList.push_back(_gLaser);
		}
	}
}