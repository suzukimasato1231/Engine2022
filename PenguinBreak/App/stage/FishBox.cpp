#include "FishBox.h"
#include<Shape.h>
#include"Easing.h"
FishBox::FishBox()
{
}

FishBox::~FishBox()
{
	for (int i = (int)fishData.size() - 1; i >= 0; i--)
	{
		delete fishData[i];
		fishData.erase(fishData.begin() + i);
	}
}

void FishBox::Init()
{
	fishOBJ = Shape::CreateOBJ("fish", true);
}

void FishBox::Update(Vec3 pPos)
{
	for (int i = 0; i < fishData.size(); i++)
	{
		float timeRote = min(fishData[i]->fishTime / time, 1.0f);
		fishData[i]->position = Easing::easeIn(fishData[i]->startPosition, pPos + fishGoalPos, timeRote);
		fishData[i]->fishTime += 1.0f;
		if (fishData[i]->fishTime >= time)
		{
			fishData[i]->endFlag = true;
		}
		if (fishData[i]->endFlag == true)
		{
			delete fishData[i];
			fishData.erase(fishData.begin() + i);
		}
	}
}

void FishBox::Draw()
{
	for (int i = 0; i < fishData.size(); i++)
	{
		Object::NoShadowDraw(fishOBJ, fishData[i]->psr, fishData[i]->position, scale, Vec3(180.0f, 0.0f, 0.0f), Vec4());
	}
}

void FishBox::Create(Vec3 pos)
{
	fishData.push_back(new FishData);
	size_t num = fishData.size() - 1;
	fishData[num]->position = pos;
	fishData[num]->startPosition = pos;
	fishData[num]->fishTime = 0.0f;
	fishData[num]->endFlag = false;
}

void FishBox::Delete()
{
	for (int i = (int)fishData.size() - 1; i >= 0; i--)
	{
		delete fishData[i];
		fishData.erase(fishData.begin() + i);
	}
}
