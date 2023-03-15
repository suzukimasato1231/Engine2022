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
	m_wallOBJ = Shape::CreateOBJ("iceWall", false, "OBJ/");
	m_deadTree = Shape::CreateOBJ("deadTree", false, "OBJ/");
	m_stone = Shape::CreateOBJ("stone", false, "OBJ/");
	m_iceArch = Shape::CreateOBJ("iceArch", false, "OBJ/");
	m_signboard = Shape::CreateOBJ("signboard", false, "OBJ/");

	m_tutorialGraph[0] = Texture::Get()->LoadTexture(L"Resources/OBJ/signboard/tutorial1.png");
	m_tutorialGraph[1] = Texture::Get()->LoadTexture(L"Resources/OBJ/signboard/tutorial2.png");
}

void FigurineOBJ::Update()
{}

void FigurineOBJ::Draw(StageData* stageObj, const bool shadowFlag)
{

	if (stageObj->fileName.compare("WALL") == 0)
	{
		Object::Draw(m_wallOBJ, stageObj->psr, stageObj->position,
			stageObj->scale, stageObj->rotation, Vec2(), 0, shadowFlag);
	}
	else if (stageObj->fileName.compare("STLON") == 0)
	{
		Object::Draw(m_stone, stageObj->psr, stageObj->position,
			stageObj->scale, stageObj->rotation, Vec2(), 0, shadowFlag);
	}
	else if (stageObj->fileName.compare("DEADTREE") == 0)
	{
		Object::Draw(m_deadTree, stageObj->psr, Vec3(stageObj->position.x, stageObj->position.y, stageObj->position.z),
			stageObj->scale, stageObj->rotation, Vec2(), 0, shadowFlag);
	}
	else if (stageObj->fileName.compare("ICEARCH") == 0)
	{
		Object::Draw(m_iceArch, stageObj->psr, stageObj->position, stageObj->scale,
			Vec3(stageObj->rotation.x, stageObj->rotation.y - 90.0f, stageObj->rotation.z), Vec2(), 0, shadowFlag);
	}
	else if (stageObj->fileName.compare("SIGNBOARD1") == 0)
	{
		Object::Draw(m_signboard, stageObj->psr, stageObj->position, stageObj->scale,
			Vec3(stageObj->rotation.x, stageObj->rotation.y - 90.0f, stageObj->rotation.z), Vec2(), m_tutorialGraph[0], shadowFlag);
	}
	else if (stageObj->fileName.compare("SIGNBOARD2") == 0)
	{
		Object::Draw(m_signboard, stageObj->psr, stageObj->position, stageObj->scale,
			Vec3(stageObj->rotation.x, stageObj->rotation.y - 90.0f, stageObj->rotation.z), Vec2(), m_tutorialGraph[1], shadowFlag);
	}
}
