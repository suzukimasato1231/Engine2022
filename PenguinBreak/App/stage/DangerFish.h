#pragma once
#include"StegeObject.h"
/// <summary>
/// 危険魚クラス
/// </summary>
class DangerFish
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DangerFish();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~DangerFish();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	void Update(StageOBJ* stageObj);
	/// <summary>
	/// 魚オブジェクト全体の更新
	/// </summary>
	void AllUpdate();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
	/// <summary>
	/// 魚作成
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="scale">スケール</param>
	/// <param name="angle">角度</param>
	/// <param name="map">ステージ位置</param>
	/// <param name="type">種類</param>
	/// <returns></returns>
	static StageOBJ SetDangerFish(const Vec3 &position, const Vec3& scale, const Vec3 &angle, const int type);
public:
	Vec3 GetFishAngle() { return m_rotation; }
private:
	ObjectData m_dangerFishOBJ;						//魚OBJ
	bool m_dangerFishFlag = false;					//魚が出てくるかどうか
	const int c_dangerFishTimeMax = 160;			//危険魚がでるまでの最大時間時間
	int m_dangerFishTime = 0;						//危険魚がでるまでの時間
	const Vec3 c_rotationFirst = { 0.0f,180.0f,0.0f };	//初期角度
	Vec3 m_rotation = { 0.0f,180.0f,0.0f };			//魚の角度
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