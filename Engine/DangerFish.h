#pragma once
#include"../Engine/App/stage/StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
private:
	ObjectData dangerFishOBJ;
	//魚が出てくるかどうか
	bool dangerFishFlag = false;
	//危険魚がでるまでの最大時間時間
	const int dangerFishTimeMax = 150;
	//危険魚がでるまでの時間
	int dangerFishTime = 0;
	//魚が進む時間
	float speed = {};
	//魚の角度
	Vec3 rotation = {};
};