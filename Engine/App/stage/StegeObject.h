#pragma once
#include"Vec.h"
#include <CollisionPrimitive.h>
#include"Object.h"
enum StageFloor
{
	NoneFloor,
	FloorNormal,	//普通の床
	Floor169,		//斜め床
	Floor11,		//斜め床
	FloorMove,		//移動床
	FloorPitfall_A,	//落とし穴A
	FloorPitfall_B,	//落とし穴B
};

enum StageType
{
	NoneOBJ = 0,
	Wall = 1,			//壁
	Goal = 2,			//ゴール
	BreakBox = 10,		//壊れる箱
	BreakBox2 = 11,		//壊れる箱ダブル
	BreakHARD = 12,		//固い箱
	BreakJUMP = 13,		//ジャンプ箱
	ICICLE = 20,		//氷柱
	ELECTRICITY = 21,	//電気
	FISHATTACK  = 22,	//魚アタック
};
struct Floor
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	int type = 0;
};

struct MoveFloorData
{
	PSR psr;
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	int time = 0;
	int moveFlag = 0;
	Vec3 speed = { 0.0f,0.0f,0.5f };
};

struct FloorPitfallData
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec3 drawAngle = {};//描画用
	Vec2 map = {};
	int time = 0;
	int moveFlag = 0;
};

struct StageOBJ
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
	int type = NoneOBJ;
};