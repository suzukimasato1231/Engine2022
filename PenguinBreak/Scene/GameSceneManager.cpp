#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
#include"../App/Particle/Particle.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	//XAudio2���
	audio->xAudio2.Reset();
}
void GameSceneManager::Initialize()
{
	//Audio�N���X�쐬
	audio = std::make_unique<Audio>();
	//���C�g�O���[�v�N���X�쐬
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(1, 1, 0));
	//���f�[�^�ǂݍ���

	//�J�����ʒu���Z�b�g
	Camera::Get()->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
	//�X�v���C�g�摜�ǂݍ���
	BGGraph.texNumber = Texture::Get()->GetShadowTexture();
	//3D�I�u�W�F�N�g�摜�ǂݍ���
	//�v���C���[�̏�����
	Player::Get()->Init();
	//�X�e�[�W
	Stage::Get()->Init();
	Particle::Get()->Init();
	ui.Init();

	decLifeStaging.Init();
}

void GameSceneManager::Init(int stageNum)
{
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	Reset(stageNum);
	this->stageNum = stageNum;
	decLifeStaging.Reset();
	changeScene = false;
	Player::Get()->ChangeMoveFlag(true);
	ui.Reset();
}

void GameSceneManager::Update()
{
	//�v���C���[�̍X�V
	if (Input::Get()->KeybordTrigger(DIK_R))
	{
		Reset(stageNum);
	}
	if (ui.GetMenuFlag() == false)
	{
		Player::Get()->Update();

		Stage::Get()->Update(Player::Get()->GetPosition());

		//�c�@���O�ɂȂ�Ȃ�����ǐ�
		if (Player::Get()->GetGameoverFlag() == false && Player::Get()->GetPosition().y > 0 && Stage::Get()->GetClearFlag() == false)
		{
			Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{ 0,0,-goalDistanceMax }, 0.0f, cameraAngle);
		}

		//�N���A������V�[���`�F���W
		if (Stage::Get()->GetClearFlag() == true)
		{
			//�v���C���[�S�[��Fbx�n��
			if (goalStagingTime <= 0 && changeScene == false)
			{
				goalStagingTime = goalStagingTimeMax;
				Player::Get()->GoalStaging(FbxGoalJump);
				Player::Get()->GetClearFlag(true);
				goalCameraAngle = cameraAngle;
				goalDistance = goalDistanceMax;
			}
			goalStagingTime--;
			if (goalCameraAngle >= goalCamraAngleMax)
			{
				goalCameraAngle -= 1.0f;
			}
			if (goalDistance >= goalDistanceMin)
			{
				goalDistance -= 1.0f;
			}

			//�J�����ړ��n��
			Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{ 0,0,-goalDistance }, 0.0f, goalCameraAngle);

			if (goalStagingTime == 0)
			{
				changeScene = true;
				changeNum = ChangeClear;
			}
		}
		Particle::Get()->Update();
		//���C�g�X�V
		lightGroup->Update();
	}
	else
	{
		Player::Get()->StopAnimation();
	}

	//�Q�[���I�[�o�[���̃Z���N�g
	if (Player::Get()->GetGameoverFlag() == true)
	{
		if (Input::Get()->KeybordTrigger(DIK_LEFT) == true || Input::Get()->ControllerDown(LButtonLeft) == true)
		{
			changeNum++;
		}
		if (Input::Get()->KeybordTrigger(DIK_RIGHT) == true || Input::Get()->ControllerDown(LButtonRight) == true)
		{
			changeNum--;
		}
		if (Input::Get()->KeybordTrigger(DIK_SPACE) == true || Input::Get()->ControllerDown(ButtonA) == true)
		{
			changeScene = true;
		}
		if (changeNum > 2)
		{
			changeNum = 1;
		}
		else if (changeNum < 1)
		{
			changeNum = 2;
		}
	}
	ui.Update(Player::Get()->GetFishNum(), Stage::Get()->GetClearFlag(), changeScene, changeNum);

	decLifeStaging.Update(Player::Get()->GetDecLifeFlag(), Player::Get()->GetGameoverFlag());
}

void GameSceneManager::Draw()
{
	//3D
	Stage::Get()->Draw(Player::Get()->GetPosition(), true);

	//�v���C���[�̕`��
	Player::Get()->Draw(true);

	Particle::Get()->Draw3D();
	//�p�[�e�B�N��
	Particle::Get()->Draw();
	Player::Get()->DrawParticle();
	Stage::Get()->DrawParicle();
	//2D
	ui.Draw(Player::Get()->GetRemanLives(),
		Player::Get()->GetGameoverFlag());

	decLifeStaging.Draw(Player::Get()->GetGameoverFlag(), changeNum);
}

void GameSceneManager::ShadowDraw()
{
	Stage::Get()->Draw(Player::Get()->GetPosition());
	//�v���C���[�̕`��
	Player::Get()->Draw();
}

void GameSceneManager::Reset(int stageNum)
{
	Player::Get()->Reset();
	Stage::Get()->MainInit(stageNum);
}

