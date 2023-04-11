#include "SceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"PostEffect.h"
SceneManager::SceneManager()
{}
SceneManager::~SceneManager()
{
	//XAudio2���
	Audio::Get()->xAudio2.Reset();
	//���f�[�^���
	Audio::SoundUnload(&m_bgm);
	Audio::SoundUnload(&m_buttonSE);

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

	BaseScene* scene = new TitleScene();
	SetNextScene(scene);


	m_changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	m_bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	m_buttonSE = Audio::SoundLoadWave("Resources/sound/SE/menu.wav");
	Audio::Get()->SoundBGMPlayLoopWave(m_bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManager::Update()
{
	Input::Get()->Update();

	//�V�[���`�F���W
	SceneChange();

	//���̃V�[���̗\�񂪂���Ȃ�
	if (nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}
		//�V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;
		//���̃V�[��������������
		scene_->Init(m_stageNum);
	}
	//�X�V
	scene_->Update(m_stageNum,m_breakBox);


	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		m_scene = Title;
		BaseScene* scene = new TitleScene();
		SetNextScene(scene);
	}
}

void SceneManager::Draw()
{
	//�e�[�x�l�擾
	m_shadowMapFar.PreDraw(DirectXBase::Get()->GetCmandList());
	Object::InitDraw();

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
	//�V�[���؂�ւ�
	switch (m_scene)
	{
	case Title:
		if (m_changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			m_changeSceneFlag = ChangeFirst;
			m_sceneMe = SelectScene;
			Audio::Get()->SoundSEPlayWave(m_buttonSE);
		}
		break;
	case SelectScene:
		if (m_changeSceneFlag == ChangeStand && scene_->GetSceneFlag() == true)
		{
			m_sceneMe = Game;
			m_changeSceneFlag = ChangeFirst;
		}
		break;
	case Game:
		if (m_changeSceneFlag == ChangeStand && scene_->GetSceneFlag() == true)
		{
			if (scene_->GetSceneNum() == static_cast<int>(ChangeStatus::ChangeClear))
			{
				m_sceneMe = Result;
			}
			else if (scene_->GetSceneNum() == static_cast<int>(ChangeStatus::ChangeRetry))
			{
				m_sceneMe = Game;
			}
			else if (scene_->GetSceneNum() == static_cast<int>(ChangeStatus::ChangeSelect))
			{
				m_sceneMe = SelectScene;
			}
			m_changeSceneFlag = ChangeFirst;
		}
		break;
	case Result:
		if (m_changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			if (scene_->GetSceneNum() == static_cast<int>(ResultNext::ResultNextStage) && m_stageNum != 3)
			{
				m_sceneMe = Game;
				if (Stage::Get()->GetBlockNum() > m_breakBox[m_stageNum - 1])
				{
					m_breakBox[m_stageNum - 1] = Stage::Get()->GetBlockNum();
				}
			}
			if (scene_->GetSceneNum() == static_cast<int>(ResultNext::ResultSelect) || m_stageNum == 3)
			{
				m_sceneMe = SelectScene;
				if (Stage::Get()->GetBlockNum() > m_breakBox[m_stageNum - 1])
				{
					m_breakBox[m_stageNum - 1] = Stage::Get()->GetBlockNum();
				}
			}
			m_changeSceneFlag = ChangeFirst;
			Audio::Get()->SoundSEPlayWave(m_buttonSE);
		}
		break;
	default:
		break;
	}

	//�V�[���`�F���W�̐F
	if (m_changeSceneFlag == ChangeFirst)
	{
		m_changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w >= 1.0f)
		{
			BaseScene* scene = nullptr;
			m_changeSceneFlag = ChangeEnd;
			switch (m_scene)
			{
			case Title:
				scene = new StageSelect();
				break;
			case SelectScene:
				scene = new GameScene();
				break;
			case Game:
				if (m_sceneMe == Result)
				{
					scene = new ResultScene();
				}
				else if (m_sceneMe == Game)
				{
					scene = new GameScene();
				}
				else if (m_sceneMe == SelectScene)
				{
					scene = new StageSelect();
				}
				break;
			case Result:
				if (m_sceneMe == Game)
				{
					m_stageNum++;
					scene = new GameScene();
				}
				else if (m_sceneMe == SelectScene)
				{
					scene = new StageSelect();
				}
				break;
			default:
				break;
			}
			SetNextScene(scene);
			m_scene = m_sceneMe;
		}
	}
	else if (m_changeSceneFlag == ChangeEnd)
	{
		m_changeSceneColor -= Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w <= 0.0f)
		{
			m_changeSceneFlag = ChangeStand;
		}
	}
}
