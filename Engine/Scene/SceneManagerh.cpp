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

	titleScene.Initialize();
	titleScene.Init();
	//�Q�[���V�[��
	gameScene.Initialize();
	gameScene.Init(0);
	stageScene.Initialize();
	resultScene.Init();
	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());

}

void SceneManagerh::Update()
{
	Input::Get()->Update();
	//�V�[���؂�ւ�
	if (scene == Title)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		{
			scene = SelectScene;
			stageScene.Init();
		}
	}
	else if (scene == SelectScene)
	{
		if (stageScene.GetSelectFlag() == true)
		{
			scene = GameScene;
			gameScene.Init(stageScene.GetStageNum());
		}
	}
	else if (scene == GameScene)
	{
		if (gameScene.GetChangeScene())
		{
			scene = Result;
			resultScene.Init();
		}
	}
	else if (scene == Result)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		{
			scene = Title;
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
}

void SceneManagerh::Draw()
{
	//�`��J�n

	//�I�u�W�F�N�g�`��O����
	Object::Get()->PreDraw();
	Sprite::Get()->PreDraw();
	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
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
	}
	else if (scene == Result)
	{
		resultScene.Draw();
	}
	DebugText::Get()->DrawAll();
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();
	//�|�X�g�G�t�F�N�g�̕`��
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());
	_DirectX::Get()->ResourceBarrier();
}
