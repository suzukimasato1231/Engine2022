#pragma once
#include"./StegeObject.h"
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
};

