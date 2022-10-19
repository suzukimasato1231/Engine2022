#pragma once
#include"../stage/StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//初期化処理
	void Init();
	//更新処理
	void Update(StageOBJ* stageObj);
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
	//魚の角度
	Vec3 rotation = { 0.0f,180.0f,0.0f };
	//一番上のとき
	Vec3 start_end = { -50.0f,65.0f,0.0f };
	const float start_endTimeMax = 100.0f;
	float start_endTime = 0.0f;
	//一番下の時
	Vec3 end_end = { -100.0f,-40.0f,0.0f };
	const float end_endTimeMax = 100.0f;
	float end_endTime = 0.0f;
	//危険魚のサイズ
	const Vec3 fishSize = { 12.5f,12.5f,12.5f };
};