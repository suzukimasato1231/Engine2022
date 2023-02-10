#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"FBXObject3d.h"
#include"Staging.h"
#include<memory>
#include <Audio.h>
#include"PlayerFBX.h"
enum DieType
{
	DIENULL,
	FALLDOWN,
	ELECTDIE,
	EATDIE,
	DIENOW,
};

/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public Singleton<Player>
{
public:
	friend Singleton<Player>;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	//デスコンストラクタ
	~Player();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	void Update();						//更新

	void Draw(bool shadowFlag = false);//描画

	void DrawParticle();//プレイヤーが死んだときのパーティクル

	void SetPosition(const Vec3& position);

	/// <summary>
	/// trueにする
	/// </summary>
	void GroundFlag();

	void Reset();

	void GetBlockStepOnFlag() { blockStepOnFlag = true; }

	void JumpPoweZero() { jumpPower = 0; }

	//2D false 3D true
	void ChangeMoveFlag(bool moveFlag) { Player::moveFlag = moveFlag; }

	void GetJumpBox() { jumpBoxFlag = true; }
	//箱を壊したか
	void ChangeBreakFlag() { changeBreakFlag = true; }

	void DieType(int type) { if (dieType != DIENOW) { Player::dieType = type; } }

	void Delete();

	void FishDie(const Vec3& pos, const Vec3& angle) { fishDiePos = pos, this->fishDieAngle, angle; }
	//ゴール時の演出
	void GoalStaging(int fbxType);

	void GetClearFlag(bool flag) { clearFlag = flag; }

	int GetDecLifeFlag() { return decLifeTime; }

	void StopAnimation();
private:
	/// <summary>
	/// FBXの描画
	/// </summary>
	void FbxDraw(bool shadowFlag);
	/// <summary>
	/// プレイヤー移動
	/// </summary>
	void Move();
	/// <summary>
	/// プレイヤージャンプ
	/// </summary>
	void Jump();

	//落ちて死亡したとき
	void FallDie();

	void Fish();

	void RedFishDie();

	/// <summary>
	/// スピン攻撃
	/// </summary>
	void SpinAttack();

public://取得系
	//座標
	inline Vec3 GetPosition() { return position; }

	inline Vec3 GetOldPosition() { return oldPosition; }

	inline Vec3 GetPSize() { return pScale; }

	inline Box GetBox() { return pBox; }

	inline Vec3 GetVec() { return vec; }

	inline float GetJumpPower() { return jumpPower; }

	inline bool GetGroundFlag() { return groundFlag; }

	inline bool GetOldGroundFlag() { return oldGroundFlag; }
	//残機数獲得
	inline int GetRemanLives() { return remainLives; }

	inline int GetFishNum() { return fishNum; }

	inline bool GetGameoverFlag() { return gameoverFlag; }

	inline bool GetIsFishDie() { return isFishDie; }

	inline Box GetSpinBox() { return spinAttack; }

	inline bool GetSpinFlag() { return spinFlag; }
private:
	//2D false 3D true
	bool moveFlag = false;

	bool gameoverFlag = false;
	bool clearFlag = false;

	ObjectData playerObject;			//プレイヤーオブジェクト
	PSR psr = {};
	Vec3 position{ 94.0f,14.0f,80.0f };	//座標
	Vec3 oldPosition{};					//1つ前の座標
	Vec3 speed{ 2.0f,2.0f,2.0f };		//プレイヤースピード
	Vec3 scale{ 2.5f,2.5f,2.5f };		//大きさ
	Vec3 angle{ -30.0f,180.0f,0.0f };	//角度
	Vec3 pScale = { 12.0f,5.0f,12.0f };	//
	Box pBox;							//プレイヤーの箱
	Vec3 vec = {};

	bool changeBreakFlag = false;

	const int remainLivesMax = 3;		//１ステージの残機数
	int remainLives = 3;				//残機

	//ジャンプ
	const float jumpPowerMax = 8.0f;
	const float jumpBoxPowerMax = 9.0f;	//ジャンプ台のジャンプパワー
	bool jumpBoxFlag = false;
	float jumpPower = 8.0f;				//ジャンプパワー
	float jumpPowerDelay = 0.2f;
	float gravity = 5.0f;				//重力
	bool groundFlag = false;			//地面に接しているかどうか
	bool oldGroundFlag = false;			//地面に接していたかどうか
	bool blockStepOnFlag = false;		//ブロックを踏んで壊したかどうか

	//スピン
	Box spinAttack = {};
	const float spinScale = 12.0f;
	const int spinCoolTimeMax = 100;
	int spinCoolTime = 0;
	bool spinFlag = false;

	//魚
	bool fishFlag = false;
	int fishNum = 0;

	//プレイヤー演出
	Staging staging;
	int dieNowTime = 0;
	int dieType = DIENULL;

	const int walkTimeMax = 5;
	int walkTime = walkTimeMax;
	//ステージ開始時の演出フラグ
	bool starStaging = false;
	const int startTimeMax = 60;
	int startTime = 0;
	//魚死亡時の情報
	Vec3 fishDiePos = {};
	Vec3 fishDieAngle = {};
	bool isFishDie = false;

	int decLifeTime = 0;

	//FBXクラス
	PlayerFBX pFbx;

	//音データ
	int audioTime = 0;
	SoundData walkSE = {};
	SoundData fallSE = {};
	SoundData electSE = {};

};