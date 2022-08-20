#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
class Enemy
{
private://構造体

public:
	Enemy();//コンストラクタ

	~Enemy();//ですコンストラクタ

	 void Init();//初期化

	void Update();//更新

	void Draw();//描画

	Vec3 GetPos() { return pos; }

	Vec3 GetSize() { return eSize; }

	void  SetPos(Vec3 pos) { Enemy::pos = pos; }
private:
	Vec3 pos = {};
	int eNum = 2;
	const Vec3 eSize = { 10.0f,5.0f,10.0f };
public://取得系
	int GetENum() { return eNum; }
};