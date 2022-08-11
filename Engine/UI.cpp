#include "UI.h"
#include"Stage.h"
#include"DebugText.h"
UI::UI()
{
}
UI::~UI()
{
}
void UI::Init()
{
	boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/fish.png");
}

void UI::Update()
{

}

void UI::Draw()
{
	//�v���C���[�c�@

	//�󂵂��������̉�
	//���W�v�f
	Sprite::Get()->Draw(boxGraph, Vec2(), 80.0f, 80.0f);
	DebugText::Get()->Print(10, 10, 2, "blockNum:%d",Stage::Get()->GetBlockNum());
	DebugText::Get()->Print(10, 40, 2, "blockMax:%d", Stage::Get()->GetStageBlock());
}
