#pragma once
#include"StegeObject.h"
#include"Object.h"
#include"LoadCSV.h"
/// <summary>
/// 箱クラス
/// </summary>
class BlockBox
{
public:
	BlockBox() {};

	~BlockBox() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// プレイヤーと箱の当たり判定
	/// </summary>
	/// <param name="stageObj">オブジェクト情報</param>
	/// <param name="X">X軸の位置</param>
	/// <param name="Z">Z軸の位置</param>
	void PlayerHit(StageOBJ* stageObj, const int X, const int Z);
	/// <summary>
	/// スピンと箱の当たり判定
	/// </summary>
	/// <param name="stageObj">オブジェクト情報</param>
	/// <param name="X">X軸の位置</param>
	/// <param name="Z">Z軸の位置</param>
	void PlayerSpinHit(StageOBJ* stageObj, const int X, const int Z);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <returns></returns>
	void Draw(StageOBJ* stageObj, bool shadowFlag);
private:
	/// <summary>
	/// 爆弾演出
	/// </summary>
	void BombUpdate();
public:
	StageOBJ* GetObj_Data() { return obj_data; }

	StageOBJ GetObj_Data(int i) { return obj_data[i]; }

	int GetBox_Count() { return box_count; }

	bool GetIs_Hit() { return is_hit; }

	StageOBJ GetObj_Spin(int i) { return obj_spin[i]; }

	int GetSpin_Count() { return spin_count; }

	bool GetIs_Spin() { return is_spin; }

	Vec3 GetBoxScale() { return breakBoxScale; }
private:
	ObjectData breakBoxOBJ = {};
	//箱の大きさ
	const Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
	//壊れる箱の画像
	int normalBoxGraph = 0;
	//固い箱の画像
	int hardBoxGraph = 0;
	//ジャンプの箱の画像
	int jumpBoxgraph = 0;
	//爆弾の箱の画像
	int bombBoxGraph = 0;
	Vec3 bombBoxAngle = {};							//爆弾角度
	const Vec3 bombSpeedAngle = { 0.0f,2.0f,0.0f };	//回転速度
	bool bombBoxFlag = false;						//爆弾演出フラグ
	int bombTime = 0;								//開店時間
	const int bombTimeMax = 45;						//回転時間最大
	const Vec3 bombPlasSpeed = {0.0f,0.2f,0.0f};	//跳ねる速度
	Vec3 bombPlas = {0.0f,0.0f,0.0f};				//爆弾箱の跳ねる距離

	//接触時の判定に使う箱
	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[5] = {};
	//スピンの当たり判定に使う箱
	bool is_spin = false;
	int spin_count = 0;
	StageOBJ obj_spin[5] = {};
};

