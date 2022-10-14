#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include"Camera.h"
#include"Shape.h"
#include"Input.h"
#include"Texture.h"

TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{
	titlePlayer = Shape::CreateOBJ("pengin", true);
	box = Shape::CreateOBJ("cube");
	boxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	titleButtonGraph = Sprite::Get()->SpriteCreate(L"Resources/titleButton.png");
	titleGraph = Sprite::Get()->SpriteCreate(L"Resources/Title.png");
}

void TitleScene::Init()
{
	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
}

void TitleScene::Update()
{
	buttonTime++;
	if (buttonTime >= 60)
	{
		buttonTime = 0;
	}
}

void TitleScene::Draw()
{
	//3D
	Object::Draw(titlePlayer, titlePsr,Vec3(10.0f, -3.0f, 0.0f), Vec3(1, 1, 1), Vec3(0.0f, 10.0f, 0.0f), Vec4(), titlePlayer.OBJTexture, true);

	Object::Draw(box, boxPsr,Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2), Vec3(0.0f, 10.0f, 0.0f), Vec4(), boxGraph, true);

	//UI
	Sprite::Get()->Draw(titleGraph, Vec2(0.0f, 0.0f), static_cast<float>(window_width), static_cast<float>(window_height));
	if (buttonTime >= 30)
	{
		Sprite::Get()->Draw(titleButtonGraph, Vec2(420.0f, 532.0f), 512.0f, 64.0f);
	}
}