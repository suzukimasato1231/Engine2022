#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"

TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
	safe_delete(lightGroup);
	safe_delete(camera);
	safe_delete(audio);
}
void TitleScene::Initialize()
{
	//Audio�N���X�쐬
	audio = Audio::Create();
	//�J�����N���X�쐬
	camera = Camera::Create();
	//���C�g�O���[�v�N���X�쐬
	lightGroup = LightGroup::Create();
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
}

void TitleScene::Init()
{
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object::SetCamera(camera);
	Object::SetLight(lightGroup);
}

void TitleScene::Update()
{
	
}

void TitleScene::Draw()
{
	//�w�i�`��
	DebugText::Instance()->Print(10.0f, 10.0f, 3, "Title");
}
