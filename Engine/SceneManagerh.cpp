#include "SceneManagerh.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
SceneManagerh::SceneManagerh()
{}
SceneManagerh::~SceneManagerh()
{
	safe_delete(postEffect);
}
void SceneManagerh::Initialize()
{
	//�ėp�@�\
	//�Q�[���E�B���h�E�̍쐬
	_Window::Instance()->CreateGameWindow();
	// DirectX����������
	_DirectX::Instance()->Initilize();
	//���͂̏�����
	Input::Instance()->Initialize();
	//FBX������
	FbxLoader::GetInstance()->Initialize(_DirectX::Instance()->GetDevice());
	//���C�g�ÓI������
	LightGroup::StaticInitialize(_DirectX::Instance()->GetDevice());
	//�X�v���C�g�ÓI������
	Sprite::StaticInit(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList());
	//�e�L�X�g�N���X������
	Texture::Instance()->Init(_DirectX::Instance()->GetDevice());
	//�f�o�b�N�e�L�X�g������
	DebugText::Instance()->Initialize();
	//�X�v���C�g�N���X�쐬
	Sprite::Instance()->Init();
	//FBX������
	FBXObject3d::SetDevice(_DirectX::Instance()->GetDevice());
	FBXObject3d::SetCmdList(_DirectX::Instance()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	//�}�`���f��������
	Shape::Init(_DirectX::Instance()->GetDevice());
	//�p�[�e�B�N��������
	ParticleManager::StaticInitialize(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList(), window_width, window_height);
	//3D�I�u�W�F�N�g������
	Object::Init(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList());
	//�Q�[���V�[��
	GameSceneManager::Instance()->Initialize();
	GameSceneManager::Instance()->Init();

	TitleScene::Instance()->Initialize();
	TitleScene::Instance()->Init();

	postEffect = new PostEffect;
	postEffect->Initialize(_DirectX::Instance()->GetDevice());

}

void SceneManagerh::Update()
{


	Input::Instance()->Update();

	if (scene == Title)
	{
		if (Input::Instance()->KeybordTrigger(DIK_SPACE))
		{
			scene = GameScene;
			GameSceneManager::Instance()->Init();
		}
	}
	else if (scene == GameScene)
	{
		
	}

	if (scene == Title)
	{
		TitleScene::Instance()->Update();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Instance()->Update();
	}


}

void SceneManagerh::Draw()
{
	//�`��J�n

	//�I�u�W�F�N�g�`��O����
	Object::Instance()->PreDraw();
	Sprite::Instance()->PreDraw();
	postEffect->PreDrawScene(_DirectX::Instance()->GetCmandList());
	if (scene == Title)
	{
		TitleScene::Instance()->Draw();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Instance()->Draw();
	}

	DebugText::Instance()->DrawAll();
	postEffect->PostDrawScene(_DirectX::Instance()->GetCmandList());

	_DirectX::Instance()->PreDraw();
	//�|�X�g�G�t�F�N�g�̕`��
	postEffect->Draw(_DirectX::Instance()->GetCmandList());
	_DirectX::Instance()->ResourceBarrier();
}
