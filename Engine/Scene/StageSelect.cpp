#include "StageSelect.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"

StageSelect::StageSelect()
{}
StageSelect::~StageSelect()
{
}
void StageSelect::Initialize()
{
}

void StageSelect::Init()
{}

void StageSelect::Update()
{
	//ƒXƒe[ƒW‘I‘ð
	if (Input::Get()->KeybordTrigger(DIK_LEFT))
	{
		stageNum--;
		if (stageNum <= 0)
		{
			stageNum = 1;
		}
	}
	if (Input::Get()->KeybordTrigger(DIK_RIGHT))
	{
		stageNum++;
		if (stageNum >= stageNumMax)
		{
			stageNum = stageNumMax;
		}
	}
}

void StageSelect::Draw()
{
	//”wŒi•`‰æ
	DebugText::Get()->Print(10.0f, 10.0f, 3, "Select");
	DebugText::Get()->Print(10.0f, 40.0f, 3, "StageNum:%d",stageNum);
}
