#pragma once
#include"./StegeObject.h"
/// <summary>
/// âÒì]è∞
/// </summary>
class FloorPitfall
{
public:
	FloorPitfall();

	~FloorPitfall();

	void Init();

	void Update(Floor* floorData);

	void Draw(Floor* floorData, const bool shadowFlag);
private:
	ObjectData pitfallOBJ;
	int pitfallGraph = 0;
	const int pitfallTime = 70;
};

