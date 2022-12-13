#include "SceneManagerh.h"
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
	Audio::SoundUnload(&bgm);
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
	//�}�`���f��������
	Shape::Init(_DirectX::Get()->GetDevice());
	//�p�[�e�B�N��������
	ParticleManager::StaticInitialize(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList(), window_width, window_height);
	//3D�I�u�W�F�N�g������
	Object::Init(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList());

	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());
	////�e
	ShadowMap::Get()->Init();
	Texture::Get()->LoadShadowTexture(ShadowMap::Get()->GetTexbuff());
	Texture::Get()->LoadCameraTexture(PostEffect::Get()->GetDepth());

	//���쐬
	Audio::Get()->Init();
	titleScene.Initialize();
	////�Q�[���V�[��
	gameScene.Initialize();
	gameScene.Init(0);
	stageScene.Initialize();
	resultScene.Initialize();
	resultScene.Init();
	titleScene.Init();

	changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	Audio::Get()->SoundBGMPlayLoopWave(bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManagerh::Update()
{
	Input::Get()->Update();

	//�V�[���؂�ւ�
	if (scene == Title)
	{
		if (changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			changeSceneFlag = ChangeFirst;
			sceneMe = SelectScene;
		}
	}
	else if (scene == SelectScene)
	{
		if (changeSceneFlag == ChangeStand && stageScene.GetSelectFlag() == true)
		{
			sceneMe = GameScene;
			changeSceneFlag = ChangeFirst;
		}
	}
	else if (scene == GameScene)
	{
		if (changeSceneFlag == ChangeStand && gameScene.GetChangeScene())
		{
			if (gameScene.GetChangeNum() == 0)
			{
				sceneMe = Result;
			}
			else if (gameScene.GetChangeNum() == 1)
			{
				sceneMe = GameScene;
			}
			else if (gameScene.GetChangeNum() == 2)
			{
				sceneMe = SelectScene;
			}
			changeSceneFlag = ChangeFirst;
		}
	}
	else if (scene == Result)
	{
		if (changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			if (resultScene.GetScene() == ResultNextStage&&stageScene.GetStageNum()!=3)
			{
				sceneMe = GameScene;
			}
			if (resultScene.GetScene() == ResultSelect || stageScene.GetStageNum() == 3)
			{
				sceneMe = SelectScene;
			}
			changeSceneFlag = ChangeFirst;
		}
	}
	//�X�V
	if (scene == Title)
	{
		titleScene.Update();
	}
	else if (scene == SelectScene)
	{
		stageScene.Update();
	}
	else if (scene == GameScene)
	{
		gameScene.Update();
	}
	else if (scene == Result)
	{
		resultScene.Update();
	}


	//�V�[���`�F���W
	if (changeSceneFlag == ChangeFirst)
	{
		changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (changeSceneColor.w >= 1.0f)
		{
			changeSceneFlag = ChangeEnd;
			switch (scene)
			{
			case Title:
				stageScene.Init();
				break;
			case SelectScene:
				gameScene.Init(stageScene.GetStageNum());
				break;
			case GameScene:
				if (sceneMe == Result)
				{
					resultScene.Init();
				}
				else if (sceneMe == GameScene)
				{
					gameScene.Init(stageScene.GetStageNum());
				}
				else if (sceneMe == SelectScene)
				{
					stageScene.Init();
				}
				break;
			case Result:
				if (sceneMe == GameScene)
				{
					stageScene.StagePlas();
					gameScene.Init(stageScene.GetStageNum());
					
				}
				else if (sceneMe == SelectScene)
				{
					stageScene.Init();
				}
				break;
			default:
				break;
			}
			scene = sceneMe;
		}
	}
	else if (changeSceneFlag == ChangeEnd)
	{
		changeSceneColor -= Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (changeSceneColor.w <= 0.0f)
		{
			changeSceneFlag = ChangeStand;
		}
	}


	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		scene = Title;
		titleScene.Init();
	}
}

void SceneManagerh::Draw()
{
	//�e�[�x�l�擾
	ShadowMap::Get()->PreDraw(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Object::InitDraw(), Sprite::Get()->PreDraw();
	if (scene == Title)
	{
		titleScene.ShadowDraw();
	}
	else if (scene == SelectScene)
	{
		stageScene.DrawShadow();
	}
	else if (scene == GameScene)
	{
		gameScene.ShadowDraw();
	}
	else if (scene == Result)
	{
		resultScene.ShadowDraw();
	}
	ShadowMap::Get()->PostDraw(_DirectX::Get()->GetCmandList());

	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	Object::SetPipeline(Pipeline::OBJPipeline);
	Object::Get()->PreDraw(true), Object::InitDraw(), Sprite::Get()->PreDraw();
	//�J�����ڐ��̕`��
	if (scene == Title)
	{
		titleScene.Draw();
	}
	else if (scene == SelectScene)
	{
		stageScene.Draw();
	}
	else if (scene == GameScene)
	{
		gameScene.Draw();
		//ShadowMap::Get()->Draw(_DirectX::Get()->GetCmandList());
	}
	else if (scene == Result)
	{
		resultScene.Draw(stageScene.GetStageNum());
	}
	DebugText::Get()->DrawAll();
	if (changeSceneFlag == ChangeFirst || changeSceneFlag == ChangeEnd)
	{
		Sprite::Get()->Draw(changeBlack, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), changeSceneColor);
	}
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();

	////�|�X�g�G�t�F�N�g�̕`��
	//PostEffect::Get()->SetPipeline(1);
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->ResourceBarrier();
}

void SceneManagerh::Delete()
{
	titleScene.Delete();
	resultScene.Delete();
}
