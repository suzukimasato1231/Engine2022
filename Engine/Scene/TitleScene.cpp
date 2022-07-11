#include"TitleScene.h"
#include<sstream>
#include<iomanip>

TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{
}

void TitleScene::Init()
{	
}

void TitleScene::Update()
{	
}

void TitleScene::Draw()
{
	//”wŒi•`‰æ
	DebugText::Get()->Print(10.0f, 10.0f, 3, "Title");
}
