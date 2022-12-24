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
	goalOBJ = Shape::CreateOBJ("goldFish", true, "OBJ/");
}

void GoalFish::Update()
{
	goalScale.y += 1.0f;
	if (goalScale.y == 360.0f)
	{
		goalScale.y = 0.0f;
	}

}

void GoalFish::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
	Object::Draw(goalOBJ, stageObj->psr, stageObj->position, Vec3(3.0f, 3.0f, 3.0f),
		Vec3(0.0f, goalScale.y, 180.0f), Vec2(), 0, shadowFlag);
}
