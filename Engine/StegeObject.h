#pragma once
#include"Vec.h"
#include <CollisionPrimitive.h>
struct Floor
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
};

struct MoveFloorData
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	int time = 0;
	int moveFlag = 0;
	Vec3 speed = { 0.0f,0.0f,0.5f };
};

enum StageFloor
{
	NoneFloor,
	FloorNormal,//???ʂ̏?
	Floor169,	//?΂ߏ?
	Floor11,	//?΂ߏ?
	FloorMove,	//?ړ???
};

enum StageType
{
	NoneOBJ = 0,
	Wall = 1,		//??
	Goal = 2,		//?S?[??
	BreakBox = 10,	//?????锠
	BreakBox2 = 11,	//?????锠?_?u??
	BreakHARD = 12,	//?ł????_?u??
	BreakJUMP = 13,	//?W?????v??
};


struct StageOBJ
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
	int type = NoneOBJ;
};