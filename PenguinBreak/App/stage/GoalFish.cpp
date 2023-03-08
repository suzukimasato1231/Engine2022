#include "GoalFish.h"
#include"Shape.h"
GoalFish::GoalFish()
{
}

GoalFish::~GoalFish()
{
}

void GoalFish::Init()
{
	m_goalOBJ = Shape::CreateOBJ("goldFish", false, "OBJ/");
}

void GoalFish::Update()
{
	m_goalScale.y += 1.0f;
	if (m_goalScale.y == 360.0f)
	{
		m_goalScale.y = 0.0f;
	}

}

void GoalFish::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
	Object::Draw(m_goalOBJ, stageObj->psr, stageObj->position, Vec3(3.0f, 3.0f, 3.0f),
		Vec3(0.0f, m_goalScale.y, 180.0f), Vec2(), 0, shadowFlag);
}
