#include "FigurineOBJ.h"
#include"Shape.h"
#include<Texture.h>
FigurineOBJ::FigurineOBJ()
{
}

FigurineOBJ::~FigurineOBJ()
{
}

void FigurineOBJ::Init()
{
	wallOBJ = Shape::CreateOBJ("iceWall", false, "OBJ/");
	deadTree = Shape::CreateOBJ("deadTree", false, "OBJ/");
	stone = Shape::CreateOBJ("stone", false, "OBJ/");
	iceArch = Shape::CreateOBJ("iceArch", false, "OBJ/");
	signboard = Shape::CreateOBJ("signboard", false, "OBJ/");

	tutorialGraph[0] = Texture::Get()->LoadTexture(L"Resources/OBJ/signboard/tutorial1.png");
	tutorialGraph[1] = Texture::Get()->LoadTexture(L"Resources/OBJ/signboard/tutorial2.png");
}

void FigurineOBJ::Update()
{}

void FigurineOBJ::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
	switch (stageObj->type)
	{
	case Wall:
		Object::Draw(wallOBJ, stageObj->psr, Vec3(stageObj->position.x, stageObj->position.y - 22.0f, stageObj->position.z),
			Vec3(12.0f, 12.0f, 12.0f), stageObj->angle, Vec2(), 0, shadowFlag);
		break;
	case DEADTREE:
		Object::Draw(deadTree, stageObj->psr, Vec3(stageObj->position.x, stageObj->position.y, stageObj->position.z),
			Vec3(12.0f, 12.0f, 12.0f), stageObj->angle, Vec2(), 0, shadowFlag);
		break;
	case STLON:
		Object::Draw(stone, stageObj->psr, Vec3(stageObj->position.x, stageObj->position.y - 2.0f, stageObj->position.z),
			Vec3(12.0f, 16.0f, 12.0f) / 2, stageObj->angle, Vec2(), 0, shadowFlag);
		break;
	case ICEARCH:
		Object::Draw(iceArch, stageObj->psr, Vec3(stageObj->position.x + 145.0f, stageObj->position.y - 2.0f, stageObj->position.z),
			Vec3(10.2f, 10.0f, 10.5f) * 3, Vec3(0.0f, 90.0f, 0.0f), Vec2(), 0, shadowFlag);
		break;
	case SIGNBOARD1:
	case SIGNBOARD2:
		Object::Draw(signboard, stageObj->psr, Vec3(stageObj->position.x, stageObj->position.y + 6.0f, stageObj->position.z),
			Vec3(4.0f, 4.0f, 4.0f) * 3, Vec3(0.0f, -60.0f, 0.0f), Vec2(), tutorialGraph[stageObj->type - tutorialNum], shadowFlag);
		break;
	default:
		break;
	}
}
