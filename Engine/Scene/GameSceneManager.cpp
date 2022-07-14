#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
#include"../Particle.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	//XAudio2���
	audio->xAudio2.Reset();
	//���f�[�^���
	safe_delete(audio);
}
void GameSceneManager::Initialize()
{
	//Audio�N���X�쐬
	audio = Audio::Create();
	//���C�g�O���[�v�N���X�쐬
	lightGroup = LightGroup::Create();

	//���f�[�^�ǂݍ���
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetSpotLightActive(0, false);
	//�J�����ʒu���Z�b�g
	Camera::Get()->SetCamera(Vec3{0,0,-200}, Vec3{0, 0, 0}, Vec3{0, 1, 0});
	//�X�v���C�g�摜�ǂݍ���

	BGGraph = Sprite::Get()->SpriteCreate(L"Resources/backgroundA.png");


	//3D�I�u�W�F�N�g�摜�ǂݍ���
	//���f�������w�肵�ăt�@�C���ǂݍ���
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	//fbxObject1 = new FBXObject3d;
	//fbxObject1->Initialize();
	//fbxObject1->SetModel(model1);
	//�v���C���[�̏�����
	Player::Get()->Init();
	//�X�e�[�W
	Stage::Get()->Init();
	Particle::Get()->Init();

	TimeAttack::Get()->Init();

	UI::Get()->Init();
}

void GameSceneManager::Init(int stageNum)
{
	FBXObject3d::SetLight(lightGroup);
	Object::SetLight(lightGroup);
	changeScene = false;
	Reset(stageNum);
	this->stageNum = stageNum;
	Player::Get()->ChangeMoveFlag(true);
}

void GameSceneManager::Update()
{
	//�v���C���[�̍X�V

	if (Input::Get()->KeybordTrigger(DIK_R))
	{
		Reset(stageNum);
	}

	Player::Get()->Update();

	Stage::Get()->Update();

	//
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{0,0,-100}, 0.0f, 35.0f);
	
	//�N���A������V�[���`�F���W
	if (Stage::Get()->GetClearFlag() == true)
	{
		changeScene = true;
	}
	Particle::Get()->Update();
	//���C�g�X�V
	lightGroup->Update();

	TimeAttack::Get()->Update();

	UI::Get()->Update();
}

void GameSceneManager::Draw()
{
	//�w�i�`��
	//Draw�ɃJ�[�\�����킹��΃R�����g�A�E�g���Ă��邩��Ȃɂ��ǂ̕ϐ����킩���
	//Sprite::Get()->Draw(BGGraph, pos, (float)window_width, (float)window_height);

	//3D

	Stage::Get()->Draw();
	//�v���C���[�̕`��
	Player::Get()->Draw();

	Particle::Get()->Draw();

	TimeAttack::Get()->Draw();

	//2D
	UI::Get()->Draw();
}

void GameSceneManager::Reset(int stageNum)
{
	Player::Get()->Reset();
	Stage::Get()->MainInit(stageNum);
	TimeAttack::Get()->Reset();
}
