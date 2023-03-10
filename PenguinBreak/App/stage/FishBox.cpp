#include "FishBox.h"
#include<Shape.h>
#include"Easing.h"
FishBox::FishBox()
{}

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
	m_fishOBJ = Shape::CreateOBJ("fish", true, "OBJ/");
}

void FishBox::Update(const Vec3& pPos)
{
	for (int i = 0; i < fishData.size(); i++)
	{
		float timeRote = min(fishData[i]->fishTime / c_time, 1.0f);
		fishData[i]->position = Easing::easeIn(fishData[i]->startPosition, pPos + c_fishGoalPos, timeRote);
		fishData[i]->fishTime += 1.0f;
		if (fishData[i]->fishTime >= c_time)
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
	for (auto f : fishData)
	{
		Object::NoShadowDraw(m_fishOBJ, f->psr, f->position, c_scale, Vec3(180.0f, 0.0f, 0.0f), Vec2());
	}
}

void FishBox::Create(const Vec3& pos)
{
	fishData.push_back(new FishData);
	size_t num = fishData.size() - 1;
	fishData[num]->position = pos;
	fishData[num]->startPosition = pos;
	fishData[num]->fishTime = {};
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
