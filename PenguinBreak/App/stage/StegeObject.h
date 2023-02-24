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
	FloorMove2,		//移動床
};

enum StageType
{
	NoneOBJ = 0,
	Wall = 1,			//壁
	Goal = 2,			//ゴール
	BarrierWall = 3,	//バリアブロック
	BOX = 10,			//壊れる箱
	BOXDOUBLE = 11,		//壊れる箱ダブル
	BOXHARD = 12,		//固い箱
	BOXJUMP = 13,		//ジャンプ箱
	BOXBOMB = 14,		//爆弾箱
	BOX_BOMB = 15,		//壊れる箱の上に爆弾箱
	BOMB_BOX = 16,		//爆弾箱の上に壊れる箱
	ICICLE = 20,		//氷柱
	ELECTRICITY = 21,	//電気
	FISHATTACK = 22,	//魚アタック
	DEADTREE = 30,		//枯れ木
	STLON = 31,			//岩
	ICEARCH = 32,		//氷のアーチ
};
struct Floor
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	int type = 0;
	int time = 0;
	int moveFlag = 0;
	Vec3 speed = { 0.0f,0.0f,0.5f };
	Vec3 drawAngle = {};
	int size = 0;
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
	Vec3 actionPos = {};
};