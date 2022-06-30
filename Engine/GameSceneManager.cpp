#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
#include"Particle.h"
#include"Particle.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	//safe_delete(particleMan);
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	safe_delete(enemy);
	//XAudio2���
	audio->xAudio2.Reset();
	//���f�[�^���
	safe_delete(audio);
}
void GameSceneManager::Initialize()
{
	//Audio�N���X�쐬
	audio = Audio::Create();
	//�J�����N���X�쐬
	camera = Camera::Create();
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
	lightGroup->SetCircleShadowActive(0, false);
	//�J�����ʒu���Z�b�g
	camera->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
	//�X�v���C�g�摜�ǂݍ���

	BGGraph = Sprite::Instance()->SpriteCreate(L"Resources/backgroundA.png");


	//3D�I�u�W�F�N�g�摜�ǂݍ���
	//���f�������w�肵�ăt�@�C���ǂݍ���
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	fbxObject1 = new FBXObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(model1);
	//�v���C���[�̏�����
	Player::Instance()->Init();
	//�G
	enemy = new Enemy;
	enemy->Init();
	//�X�e�[�W
	Stage::Instance()->Init();
}

void GameSceneManager::Init()
{
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object::SetCamera(camera);
	Object::SetLight(lightGroup);
	changeScene = false;
	Reset();
	Particle::Instance()->Init();
}

void GameSceneManager::Update()
{
	//�v���C���[�̍X�V

	if (Input::Instance()->KeybordTrigger(DIK_R))
	{
		Reset();
		Stage::Instance()->MainInit(0);
	}

	Player::Instance()->Update(enemy);

	enemy->Update();

	Stage::Instance()->Update();

	//
	camera->FollowCamera(Player::Instance()->GetPosition(), Vec3{ 0,0,-100 }, 0.0f, 35.0f);

	//�N���A������V�[���`�F���W
	if (Stage::Instance()->GetClearFlag())
	{
		changeScene = true;
	}
	Particle::Instance()->Update();
	//���C�g�X�V
	lightGroup->Update();
}

void GameSceneManager::Draw()
{
	//�w�i�`��
	//Draw�ɃJ�[�\�����킹��΃R�����g�A�E�g���Ă��邩��Ȃɂ��ǂ̕ϐ����킩���
	//Sprite::Instance()->Draw(BGGraph, pos, (float)window_width, (float)window_height);



	Stage::Instance()->Draw();
	//�v���C���[�̕`��
	Player::Instance()->Draw();

	Particle::Instance()->Draw();

}

void GameSceneManager::Reset()
{
	Player::Instance()->Reset();
}
