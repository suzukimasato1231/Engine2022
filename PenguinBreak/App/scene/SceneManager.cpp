#include "SceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"PostEffect.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
SceneManager::SceneManager()
{}
SceneManager::~SceneManager()
{
	//XAudio2���
	Audio::Get()->xAudio2.Reset();
	//���f�[�^���
	Audio::SoundUnload(&m_bgm);
	scene_->Finalize();
	delete scene_;
}
void SceneManager::Initialize()
{
	//�ėp�@�\
	//�Q�[���E�B���h�E�̍쐬
	Window::Get()->CreateGameWindow();
	// DirectX����������
	DirectXBase::Get()->Initilize();
	//���͂̏�����
	Input::Get()->Initialize();
	//�V�F�[�_�[�̓ǂݍ���
	ShaderManager::LoadShaders();
	//���C�g�ÓI������
	LightGroup::StaticInitialize(DirectXBase::Get()->GetDevice());
	//�X�v���C�g�ÓI������
	Sprite::StaticInit(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList());
	//�e�L�X�g�N���X������
	Texture::Get()->Init(DirectXBase::Get()->GetDevice());
	Pipeline::CreatePipeline(DirectXBase::Get()->GetDevice());
	//�f�o�b�N�e�L�X�g������
	DebugText::Get()->Initialize();
	//�X�v���C�g�N���X�쐬
	Sprite::Get()->Init();
	//FBX������
	FbxLoader::GetInstance()->Initialize(DirectXBase::Get()->GetDevice());
	FBXObject3d::SetDevice(DirectXBase::Get()->GetDevice());
	FBXObject3d::SetCmdList(DirectXBase::Get()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	FBXObject3d::CreateShadowPipeline();
	//�}�`���f��������
	Shape::Init(DirectXBase::Get()->GetDevice());
	//�p�[�e�B�N��������
	ParticleManager::StaticInitialize(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList(), window_width, window_height);
	//3D�I�u�W�F�N�g������
	Object::Init(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList());

	PostEffect::Get()->Initialize(DirectXBase::Get()->GetDevice());
	////�e
	m_shadowMapFar.Init();
	Texture::Get()->LoadShadowTexture(m_shadowMapFar.GetTexbuff());
	Texture::Get()->LoadCameraTexture(PostEffect::Get()->GetDepth());

	//���쐬
	Audio::Get()->Init();
	//�v���C���[�̏�����
	Player::Get()->Init();
	//�X�e�[�W
	Stage::Get()->Init();
	//�V�[�����^�C�g���ɐݒ�
	BaseScene* scene = new TitleScene();
	SetNextScene(scene);


	m_changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	m_bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	Audio::Get()->SoundBGMPlayLoopWave(m_bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManager::Update()
{
	Input::Get()->Update();

	//�V�[���`�F���W
	SceneChange();

	//���̃V�[���̗\�񂪂���Ȃ�
	if (m_changeSceneFlag == ChangeEnd && nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}
		//�V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		scene_->SetSceneManager(this);
		//���̃V�[��������������
		scene_->Init(m_stageNum);
	}
	//�X�V
	scene_->Update(m_stageNum, m_breakBox);

	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		BaseScene* scene = new TitleScene();
		SetNextScene(scene);
	}
}

void SceneManager::Draw()
{
	//�e�[�x�l�擾
	m_shadowMapFar.PreDraw(DirectXBase::Get()->GetCmandList());
	Object::InitDraw();
	//�e�`��
	scene_->ShadowDraw();
	m_shadowMapFar.PostDraw(DirectXBase::Get()->GetCmandList());


	PostEffect::Get()->PreDrawScene(DirectXBase::Get()->GetCmandList());
	Object::InitDraw(), Sprite::Get()->PreDraw();
	//�J�����ڐ��̕`��
	scene_->Draw(m_stageNum);
	DebugText::Get()->DrawAll();
	if (m_changeSceneFlag == ChangeFirst || m_changeSceneFlag == ChangeEnd)
	{
		Sprite::Get()->Draw(m_changeBlack, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), m_changeSceneColor);
	}
	PostEffect::Get()->PostDrawScene(DirectXBase::Get()->GetCmandList());

	DirectXBase::Get()->PreDraw();
	////�|�X�g�G�t�F�N�g�̕`��
	PostEffect::Get()->Draw(DirectXBase::Get()->GetCmandList());
	//UI�`��
	scene_->SecondDraw();
	DirectXBase::Get()->ResourceBarrier();
}

void SceneManager::Delete()
{
	Object::Delete();
}

void SceneManager::SceneChange()
{
	//�V�[���`�F���W�J�n
	if (nextScene_ && m_changeSceneFlag == ChangeEmpty)
	{
		m_changeSceneFlag = ChangeFirst;
	}

	//�V�[���`�F���W�̐F
	if (m_changeSceneFlag == ChangeFirst)
	{
		m_changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w >= 1.0f)
		{
			m_changeSceneFlag = ChangeEnd;
		}
	}
	else if (m_changeSceneFlag == ChangeEnd)
	{
		m_changeSceneColor -= Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w <= 0.0f)
		{
			m_changeSceneFlag = ChangeEmpty;
		}
	}
}