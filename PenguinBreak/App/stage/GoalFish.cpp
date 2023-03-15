#include "GoalFish.h"
#include"Shape.h"
GoalFish::GoalFish()
{}

GoalFish::~GoalFish()
{}

void GoalFish::Init()
{
	m_goalOBJ = Shape::CreateOBJ("goldFish", false, "OBJ/");
}

void GoalFish::Update()
{
	m_goalAngle.y += c_angleSpeed;
	if (m_goalAngle.y == c_angleMax)
	{
		m_goalAngle.y = {};
	}
}

void GoalFish::Draw(StageData* stageObj, const bool shadowFlag)
{
	Object::Draw(m_goalOBJ, stageObj->psr, stageObj->position,c_OBJScale,
		m_goalAngle, Vec2(), 0, shadowFlag);
}
