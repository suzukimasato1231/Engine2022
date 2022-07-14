#include "ResultScene.h"
#include"DebugText.h"
#include"../Stage.h"
void ResultScene::Init()
{
}

void ResultScene::Update()
{

}

void ResultScene::Draw()
{

	DebugText::Get()->Print(10, 10, 2.0f, "breakNum%d",Stage::Get()->GetBlockNum());

	DebugText::Get()->Print(10, 30, 2.0f, "breakMaxNum%d", Stage::Get()->GetStageBlock());
}
