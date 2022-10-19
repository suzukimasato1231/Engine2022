#pragma once
#include"../Engine/App/stage/StegeObject.h"
class Electricity
{
public:
	Electricity();

	~Electricity();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
public:
	bool GetElectFlag() { return electFlag; }
private:
	//電気柱オブジェクト
	ObjectData electOBJ;
	//電気オブジェクト
	ObjectData electShockOBJ;

	//電気ON/OFF
	bool electFlag = false;
	//電気切り替え最大時間時間
	const int electTimeMax = 150;
	//切り替えまでの時間
	int electTime = 0;
};

