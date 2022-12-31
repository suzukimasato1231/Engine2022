#pragma once
#include"./StegeObject.h"
/// <summary>
/// 動く床クラス
/// </summary>
class MoveFloor
{
public:
	MoveFloor();

	~MoveFloor();

	void Init();

	void Update(Floor* floorData);

	void Draw(Floor* floorData, const bool shadowFlag);
private:
	ObjectData moveFloorOBJ;

	Vec3 speed = { 0.0f,0.0f,0.5f };
};

