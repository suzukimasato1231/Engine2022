#pragma once
#include"Object.h"
#include <CollisionPrimitive.h>

enum StageType
{
	NONEFLOOR,
	FLOORNORMAL,	//普通の床
	FLOOR169,		//斜め床
	FLOOR11,		//斜め床
	FLOORMOVE,		//移動床
	FLOORMOVE2,		//移動床
	FLOORPITFALL_A,	//落とし穴A
	FLOORPITFALL_B,	//落とし穴B
	WALL ,			//壁
	GOAL ,			//ゴール
	BARRIERWALL ,	//バリアブロック
	BOX ,			//壊れる箱
	BOXHARD ,		//固い箱
	BOXJUMP ,		//ジャンプ箱
	BOXBOMB ,		//爆弾箱
	ICICLE ,		//氷柱
	ELECTRICITY ,	//電気
	FISHATTACK ,	//魚アタック
	DEADTREE ,		//枯れ木
	STLON ,			//岩
	ICEARCH ,		//氷のアーチ
	SIGNBOARD1 ,	//看板ジャンプ
	SIGNBOARD2 ,	//看板スピン
};

struct StageData
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 rotation = {};
	//親クラス
	PSR psr = {};
	std::string fileName;
	Box box;
	int type = 0;
	int actionTime = 0;
	int actionType = 0;
	Vec3 actionPos = {};
};