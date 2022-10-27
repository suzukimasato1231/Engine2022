#pragma once
#include"StegeObject.h"
#include"ParticleManager.h"
class Electricity
{
public:
	Electricity();

	~Electricity();
	//初期化
	void Init();
	//全体的な更新
	void AllUpdate();
	//更新
	void Update(StageOBJ* stageObj, const int Z);
	//描画
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	void DrawParicle();

	static StageOBJ SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
private:
	//電気パーティクル
	void AddElect(Vec3 pos);
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
	//電気びりびり
	ParticleManager* electParicle = nullptr;
	int electParicleGraph = 0;
};

