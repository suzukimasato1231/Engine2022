#include "GameScene.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	//XAudio2解放
	audio->xAudio2.Reset();
}
void GameSceneManager::Initialize()
{
	//Audioクラス作成
	audio = std::make_unique<Audio>();
	//ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));
	//音データ読み込み

	//カメラ位置をセット
	Camera::Get()->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
	//スプライト画像読み込み
	m_BGGraph.texNumber = Texture::Get()->GetShadowTexture();

	//プレイヤーの初期化
	Player::Get()->Init();
	//ステージ
	Stage::Get()->Init();
	m_ui.Init();

	m_decLifeStaging.Init();

	m_decisionSE = Audio::SoundLoadWave("Resources/sound/SE/menu.wav");
	m_selectSE = Audio::SoundLoadWave("Resources/sound/SE/menuSelect.wav");
}

void GameSceneManager::Init(int stageNum)
{
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	Player::Get()->SetMoveFlag(true);
	Reset(stageNum);
	m_stageNum = stageNum;
	m_decLifeStaging.Reset();
	m_changeScene = false;
	m_ui.Reset();
}

void GameSceneManager::Update()
{
	//プレイヤーの更新
	if (Input::Get()->KeybordTrigger(DIK_R))
	{
		Reset(m_stageNum);
	}
	if (m_ui.GetMenuFlag() == false)
	{
		Player::Get()->Update();

		Stage::Get()->Update(Player::Get()->GetPosition());

		//残機が０にならない限り追跡
		if (Player::Get()->GetGameoverFlag() == false && Player::Get()->GetPosition().y > 0 && Stage::Get()->GetClearFlag() == false)
		{
			Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{ 0,0,-c_goalDistanceMax }, 0.0f, c_cameraAngle);
		}

		//クリアしたらシーンチェンジ
		if (Stage::Get()->GetClearFlag() == true)
		{
			//プレイヤーゴールFbx始め
			if (m_goalStagingTime <= 0 && m_changeScene == false)
			{
				m_goalStagingTime = c_goalStagingTimeMax;
				Player::Get()->GoalStaging(FbxGoalJump);
				Player::Get()->GetClearFlag(true);
				m_goalCameraAngle = c_cameraAngle;
				m_goalDistance = c_goalDistanceMax;
			}
			m_goalStagingTime--;
			if (m_goalCameraAngle >= c_goalCamraAngleMax)
			{
				m_goalCameraAngle -= c_cameraSpeed;
			}
			if (m_goalDistance >= c_goalDistanceMin)
			{
				m_goalDistance -= c_cameraSpeed;
			}

			//カメラ移動始め
			Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{ 0,0,-m_goalDistance }, 0.0f, m_goalCameraAngle);

			if (m_goalStagingTime == 0)
			{
				m_changeScene = true;
				m_changeNum = static_cast<int>(ChangeStatus::ChangeClear);
			}
		}
		//ライト更新
		lightGroup->Update();
	}
	else
	{
		Player::Get()->StopAnimation();
	}

	//ゲームオーバー時のセレクト
	if (Player::Get()->GetGameoverFlag() == true)
	{
		if (Input::Get()->KeybordTrigger(DIK_LEFT) == true || Input::Get()->ControllerDown(LButtonLeft) == true)
		{
			m_changeNum++;
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
		if (Input::Get()->KeybordTrigger(DIK_RIGHT) == true || Input::Get()->ControllerDown(LButtonRight) == true)
		{
			m_changeNum--;
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
		if (Input::Get()->KeybordTrigger(DIK_SPACE) == true || Input::Get()->ControllerDown(ButtonA) == true)
		{
			m_changeScene = true;
			Audio::Get()->SoundSEPlayWave(m_decisionSE);
		}
		if (m_changeNum >GameOverSelect)
		{
			m_changeNum = GameOverRetry;
		}
		else if (m_changeNum < GameOverRetry)
		{
			m_changeNum = GameOverSelect;
		}
	}
	m_ui.Update(Player::Get()->GetFishNum(), Stage::Get()->GetClearFlag(), m_changeScene, m_changeNum);

	m_decLifeStaging.Update(Player::Get()->GetDecLifeFlag(), Player::Get()->GetGameoverFlag());
}

void GameSceneManager::Draw()
{
	//3D
	Stage::Get()->Draw(true);

	//プレイヤーの描画
	Player::Get()->Draw(true);

	//パーティクル
	Player::Get()->DrawParticle();
	Stage::Get()->DrawParicle();
}

void GameSceneManager::ShadowDraw()
{
	Stage::Get()->Draw();
	//プレイヤーの描画
	Player::Get()->Draw();
}

void GameSceneManager::SecondDraw()
{
	m_ui.Draw(Player::Get()->GetRemanLives(),
		Player::Get()->GetGameoverFlag());

	m_decLifeStaging.Draw(Player::Get()->GetGameoverFlag(), m_changeNum);
}

void GameSceneManager::Reset(int stageNum)
{
	Player::Get()->Reset();
	Stage::Get()->MainInit(stageNum);
}

