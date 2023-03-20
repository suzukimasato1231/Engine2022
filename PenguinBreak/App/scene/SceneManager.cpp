#include "SceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"PostEffect.h"
SceneManagerh::SceneManagerh()
{}
SceneManagerh::~SceneManagerh()
{
	//XAudio2���
	Audio::Get()->xAudio2.Reset();
	//���f�[�^���
	Audio::SoundUnload(&m_bgm);
	Audio::SoundUnload(&m_buttonSE);
}
void SceneManagerh::Initialize()
{
	//�ėp�@�\
	//�Q�[���E�B���h�E�̍쐬
	_Window::Get()->CreateGameWindow();
	// DirectX����������
	_DirectX::Get()->Initilize();
	//���͂̏�����
	Input::Get()->Initialize();
	//�V�F�[�_�[�̓ǂݍ���
	ShaderManager::LoadShaders();
	//���C�g�ÓI������
	LightGroup::StaticInitialize(_DirectX::Get()->GetDevice());
	//�X�v���C�g�ÓI������
	Sprite::StaticInit(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList());
	//�e�L�X�g�N���X������
	Texture::Get()->Init(_DirectX::Get()->GetDevice());
	Pipeline::CreatePipeline(_DirectX::Get()->GetDevice());
	//�f�o�b�N�e�L�X�g������
	DebugText::Get()->Initialize();
	//�X�v���C�g�N���X�쐬
	Sprite::Get()->Init();
	//FBX������
	FbxLoader::GetInstance()->Initialize(_DirectX::Get()->GetDevice());
	FBXObject3d::SetDevice(_DirectX::Get()->GetDevice());
	FBXObject3d::SetCmdList(_DirectX::Get()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	FBXObject3d::CreateShadowPipeline();
	//�}�`���f��������
	Shape::Init(_DirectX::Get()->GetDevice());
	//�p�[�e�B�N��������
	ParticleManager::StaticInitialize(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList(), window_width, window_height);
	//3D�I�u�W�F�N�g������
	Object::Init(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList());

	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());
	////�e
	m_shadowMapFar.Init();
	Texture::Get()->LoadShadowTexture(m_shadowMapFar.GetTexbuff());
	Texture::Get()->LoadCameraTexture(PostEffect::Get()->GetDepth());

	//���쐬
	Audio::Get()->Init();
	////�Q�[���V�[��
	m_titleScene.Initialize();
	m_gameScene.Initialize();
	m_stageScene.Initialize();
	m_resultScene.Initialize();
	m_gameScene.Init(0);
	m_resultScene.Init();
	m_titleScene.Init();

	m_changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	m_bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	m_buttonSE = Audio::SoundLoadWave("Resources/sound/SE/menu.wav");
	Audio::Get()->SoundBGMPlayLoopWave(m_bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManagerh::Update()
{
	Input::Get()->Update();

	//�V�[���`�F���W
	SceneChange();

	//�X�V
	if (m_scene == Title)
	{
		m_titleScene.Update();
	}
	else if (m_scene == SelectScene)
	{
		m_stageScene.Update();
	}
	else if (m_scene == GameScene)
	{
		m_gameScene.Update();
	}
	else if (m_scene == Result)
	{
		m_resultScene.Update();
	}


	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		m_scene = Title;
		m_titleScene.Init();
	}
}

void SceneManagerh::Draw()
{
	//�e�[�x�l�擾
	m_shadowMapFar.PreDraw(_DirectX::Get()->GetCmandList());
	Object::InitDraw();
	if (m_scene == Title)
	{
		m_titleScene.ShadowDraw();
	}
	else if (m_scene == SelectScene)
	{
		m_stageScene.DrawShadow();
	}
	else if (m_scene == GameScene)
	{
		m_gameScene.ShadowDraw();
	}
	else if (m_scene == Result)
	{
		m_resultScene.ShadowDraw();
	}
	m_shadowMapFar.PostDraw(_DirectX::Get()->GetCmandList());


	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	Object::InitDraw(), Sprite::Get()->PreDraw();
	//�J�����ڐ��̕`��
	if (m_scene == Title)
	{
		m_titleScene.Draw();
	}
	else if (m_scene == SelectScene)
	{
		m_stageScene.Draw();
	}
	else if (m_scene == GameScene)
	{
		m_gameScene.Draw();
	}
	else if (m_scene == Result)
	{
		m_resultScene.Draw(m_stageScene.GetStageNum());
	}
	DebugText::Get()->DrawAll();
	if (m_changeSceneFlag == ChangeFirst || m_changeSceneFlag == ChangeEnd)
	{
		Sprite::Get()->Draw(m_changeBlack, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), m_changeSceneColor);
	}
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();
	////�|�X�g�G�t�F�N�g�̕`��
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());
	//UI�`��
	if (m_scene == GameScene)
	{
		m_gameScene.SecondDraw();
	}
	_DirectX::Get()->ResourceBarrier();
}

void SceneManagerh::Delete()
{
	Object::Delete();
}

void SceneManagerh::SceneChange()
{
	//�V�[���؂�ւ�
	if (m_scene == Title)
	{
		if (m_changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			m_changeSceneFlag = ChangeFirst;
			m_sceneMe = SelectScene;
			Audio::Get()->SoundSEPlayWave(m_buttonSE);
		}
	}
	else if (m_scene == SelectScene)
	{
		if (m_changeSceneFlag == ChangeStand && m_stageScene.GetSelectFlag() == true)
		{
			m_sceneMe = GameScene;
			m_changeSceneFlag = ChangeFirst;
		}
	}
	else if (m_scene == GameScene)
	{
		if (m_changeSceneFlag == ChangeStand && m_gameScene.GetChangeScene())
		{
			if (m_gameScene.GetChangeNum() == 0)
			{
				m_sceneMe = Result;
			}
			else if (m_gameScene.GetChangeNum() == 1)
			{
				m_sceneMe = GameScene;
			}
			else if (m_gameScene.GetChangeNum() == 2)
			{
				m_sceneMe = SelectScene;
			}
			m_changeSceneFlag = ChangeFirst;
		}
	}
	else if (m_scene == Result)
	{
		if (m_changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			if (m_resultScene.GetScene() == ResultNextStage && m_stageScene.GetStageNum() != 3)
			{
				m_sceneMe = GameScene;
				m_stageScene.SetBreakBoxNum(Stage::Get()->GetBlockNum());
			}
			if (m_resultScene.GetScene() == ResultSelect || m_stageScene.GetStageNum() == 3)
			{
				m_sceneMe = SelectScene;
				m_stageScene.SetBreakBoxNum(Stage::Get()->GetBlockNum());
			}
			m_changeSceneFlag = ChangeFirst;
			Audio::Get()->SoundSEPlayWave(m_buttonSE);
		}
	}


	//�V�[���`�F���W�̐F
	if (m_changeSceneFlag == ChangeFirst)
	{
		m_changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w >= 1.0f)
		{
			m_changeSceneFlag = ChangeEnd;
			switch (m_scene)
			{
			case Title:
				m_stageScene.Init();
				break;
			case SelectScene:
				m_gameScene.Init(m_stageScene.GetStageNum());
				break;
			case GameScene:
				if (m_sceneMe == Result)
				{
					m_resultScene.Init();
				}
				else if (m_sceneMe == GameScene)
				{
					m_gameScene.Init(m_stageScene.GetStageNum());
				}
				else if (m_sceneMe == SelectScene)
				{
					m_stageScene.Init();
				}
				break;
			case Result:
				if (m_sceneMe == GameScene)
				{
					m_stageScene.StagePlas();
					m_gameScene.Init(m_stageScene.GetStageNum());

				}
				else if (m_sceneMe == SelectScene)
				{
					m_stageScene.Init();
				}
				break;
			default:
				break;
			}
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