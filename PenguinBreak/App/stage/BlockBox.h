#pragma once
#include"StegeObject.h"
#include"Object.h"
/// <summary>
/// 箱クラス
/// </summary>
class BlockBox
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BlockBox() {};
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
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
	void PlayerHit(StageData* stageObj);
	/// <summary>
	/// スピンと箱の当たり判定
	/// </summary>
	/// <param name="stageObj">オブジェクト情報</param>
	/// <param name="X">X軸の位置</param>
	/// <param name="Z">Z軸の位置</param>
	void PlayerSpinHit(StageData* stageObj);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <returns></returns>
	void Draw(StageData* stageObj, bool shadowFlag);
private:
	/// <summary>
	/// 爆弾演出
	/// </summary>
	void BombUpdate();
public:
	StageData* GetObj_Data() { return m_obj_data; }

	StageData GetObj_Data(int i) { return m_obj_data[i]; }

	int GetBox_Count() { return m_box_count; }

	bool GetIs_Hit() { return m_is_hit; }

	StageData GetObj_Spin(int i) { return m_obj_spin[i]; }

	int GetSpin_Count() { return m_spin_count; }

	bool GetIs_Spin() { return m_is_spin; }

	Vec3 GetBoxScale() { return c_breakBoxScale; }
private:
	ObjectData m_breakBoxOBJ = {};
	//箱の大きさ
	const Vec3 c_breakBoxScale = { 20.0f,20.0f,20.0f };
	//壊れる箱の画像
	TextureData m_normalBoxGraph = {};
	//固い箱の画像
	TextureData m_hardBoxGraph = {};
	//ジャンプの箱の画像
	TextureData m_jumpBoxgraph = {};
	//爆弾の箱の画像
	TextureData m_bombBoxGraph = {};
	Vec3 m_bombBoxAngle = {};							//爆弾角度
	const Vec3 c_bombSpeedAngle = { 0.0f,2.0f,0.0f };	//回転速度
	bool m_bombBoxFlag = false;							//爆弾演出フラグ
	int m_bombTime = 0;									//開店時間
	const int c_bombTimeMax = 45;						//回転時間最大
	const Vec3 c_bombPlasSpeed = {0.0f,0.2f,0.0f};		//跳ねる速度
	Vec3 m_bombPlas = {0.0f,0.0f,0.0f};					//爆弾箱の跳ねる距離
	//最大ヒット数
	const int hitMax = 4;
	//接触時の判定に使う箱
	bool m_is_hit = false;
	int m_box_count = 0;
	StageData m_obj_data[5] = {};
	//スピンの当たり判定に使う箱
	bool m_is_spin = false;
	int m_spin_count = 0;
	StageData m_obj_spin[5] = {};
};

