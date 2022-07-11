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

enum BlockType
{
	BLOCKNORMAL,
	BLOCKHRDE,
	BLOCKJUMP,
};

struct BreakBoxData
{
	
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
	int type = 0;
};

struct WallData
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
};

struct GoalData
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
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
	FloorNormal,//普通の床
	Floor169,	//斜め床
	Floor11,	//斜め床
	FloorMove,	//移動床
};

enum StageOBJ
{
	NoneOBJ = 0,
	Wall = 1,		//壁
	Goal = 2,		//ゴール
	BreakBox = 10,	//壊れる箱
	BreakBox2 = 11,	//壊れる箱ダブル
	BreakHARD = 12,	//固い箱ダブル
	BreakJUMP = 13,	//ジャンプ箱
};

