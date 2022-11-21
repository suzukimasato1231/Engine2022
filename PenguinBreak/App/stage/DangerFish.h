#pragma once
#include"StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//初期化処理
	void Init();
	//更新処理
	void Update(StageOBJ* stageObj);

	void AllUpdate();
	//描画処理
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
public:
	Vec3 GetFishAngle() { return m_rotation; }

private:
	ObjectData m_dangerFishOBJ;
	//魚が出てくるかどうか
	bool m_dangerFishFlag = false;
	//危険魚がでるまでの最大時間時間
	const int c_dangerFishTimeMax = 160;
	//危険魚がでるまでの時間
	int m_dangerFishTime = 0;
	//魚の角度
	Vec3 m_rotation = { 0.0f,180.0f,0.0f };
	//一番上のとき
	Vec3 m_start_end = { -50.0f,65.0f,0.0f };
	const float c_start_endTimeMax = 50.0f;
	float m_start_endTime = 0.0f;
	//一番下の時
	Vec3 m_end_end = { -100.0f,-40.0f,0.0f };
	const float c_end_endTimeMax = 50.0f;
	float m_end_endTime = 0.0f;
	//危険魚のサイズ
	const Vec3 c_fishSize = { 12.5f,12.5f,12.5f };
};