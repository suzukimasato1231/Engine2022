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

	titleScene.Initialize();
	//�Q�[���V�[��
	gameScene.Initialize();
	gameScene.Init(0);
	stageScene.Initialize();
	resultScene.Init();
	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());
	//�e
	ShadowMap::Get()->Init();
	Texture::Get()->LoadShadowTexture(ShadowMap::Get()->GetTexbuff());
	titleScene.Init();
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
			titleScene.Init();
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

	//�e�[�x�l�擾
	ShadowMap::Get()->PreDraw(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Sprite::Get()->PreDraw();
	if (scene == Title)
	{
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
	}
	ShadowMap::Get()->PostDraw(_DirectX::Get()->GetCmandList());



	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Sprite::Get()->PreDraw();
	//�J�����ڐ��̕`��
	Object::SetPipeline(Pipeline::OBJPipeline);
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
		/*if (Input::Get()->KeybordTrigger(DIK_C))
		{
			if (Flag == false){	Flag = true;}
			else { Flag = false; }
		}*/
		//if (Flag == false){
		gameScene.Draw();
		/*}
		else {
			ShadowMap::Get()->Draw(_DirectX::Get()->GetCmandList());
		}*/
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
