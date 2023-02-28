#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"FBXObject3d.h"
#include"Staging.h"
#include<memory>
#include <Audio.h>
#include"PlayerFBX.h"
/// <summary>
/// 死亡タイプ
/// </summary>
enum DieType
{
	DIENULL,
	FALLDOWN,
	ELECTDIE,
	EATDIE,
	BOMBDIE,
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
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(bool shadowFlag = false);
	/// <summary>
	/// プレイヤーから出るパーティクル描画
	/// </summary>
	void DrawParticle();
	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="position">設定する座標</param>
	void SetPosition(const Vec3& position);
	/// <summary>
	/// 地面接地trueにする
	/// </summary>
	void ActivateGround() { groundFlag = true; }
	/// <summary>
	/// 値リセット
	/// </summary>
	void Reset();
	/// <summary>
	///　箱をジャンプで壊したか
	/// </summary>
	void ActivateBlockStepOn() { blockStepOnFlag = true; }
	/// <summary>
	/// ジャンプ力をゼロにする
	/// </summary>
	void JumpPoweZero() { jumpPower = 0; }
	/// <summary>
	/// 2D false 3D true　
	/// </summary>
	/// <param name="moveFlag">2Dか3Dのフラグ</param>
	void ChangeMoveFlag(bool moveFlag) { Player::moveFlag = moveFlag; }
	/// <summary>
	/// ジャンプ箱を踏んだか
	/// </summary>
	void ActivateJumpBox() { jumpBoxFlag = true; }
	/// <summary>
	/// 箱を壊したか
	/// </summary>
	void ActivateChangeBreak() { changeBreakFlag = true; }

	void DieType(int type) { if (dieType != DIENOW) { Player::dieType = type; } }

	void Delete();

	void FishDie(const Vec3& pos, const Vec3& angle) { fishDiePos = pos, this->fishDieAngle, angle; }
	//ゴール時の演出
	void GoalStaging(int fbxType);

	void GetClearFlag(bool clearFlag) { this->clearFlag = clearFlag; }

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
	/// <summary>
	/// 魚の加算
	/// </summary>
	void Fish();
	/// <summary>
	/// 赤い魚に捕まったときの処理
	/// </summary>
	void RedFishDie();
	/// <summary>
	/// スピン攻撃
	/// </summary>
	void SpinAttack();
	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void AnimationUpdate();
	/// <summary>
	/// 音の更新
	/// </summary>
	void AudioUpdate();
public://取得系
	inline Vec3 GetPosition() { return position; }

	inline Vec3 GetOldPosition() { return oldPosition; }

	inline Vec3 GetPSize() { return pScale; }

	inline Box GetBox() { return pBox; }

	inline Vec3 GetVec() { return vec; }

	inline float GetJumpPower() { return jumpPower; }

	inline bool GetGroundFlag() { return groundFlag; }

	inline bool GetOldGroundFlag() { return oldGroundFlag; }
	
	inline int GetRemanLives() { return remainLives; }

	inline int GetFishNum() { return fishNum; }

	inline bool GetGameoverFlag() { return gameoverFlag; }

	inline bool GetIsFishDie() { return isFishDie; }

	inline Box GetSpinBox() { return spinAttack; }

	inline bool GetSpinFlag() { return spinFlag; }
private:
	//ゲームフラグ
	bool moveFlag = false;								//2D false 3D true
	bool gameoverFlag = false;							//ゲームオーバーかどうか
	bool clearFlag = false;								//クリアしたかどうか
	//プレイヤーステータス
	ObjectData playerObject;							//プレイヤーオブジェクト
	PSR psr = {};										//プレイヤーの位置座標大きさ保存用
	Vec3 position = { 94.0f,14.0f,80.0f };				//座標
	const Vec3 firstPosition = { 90.0f,25.0f,80.0f };	//初期位置
	Vec3 oldPosition = {};								//1つ前の座標
	const Vec3 speed = { 2.0f,2.0f,2.0f };				//走るスピード
	const Vec3 walkSpeed = { 1.0f,1.0f,1.0f };			//歩くスピード
	Vec3 angle = { -30.0f,180.0f,0.0f };				//角度
	const Vec3 firstAngle = { -30.0f,180.0f,0.0f };		//最初の角度
	Vec3 pScale = { 12.0f,5.0f,12.0f };					//プレイヤーの大きさ
	Box pBox;											//プレイヤーBOX
	Vec3 vec = {};
	bool changeBreakFlag = false;

	const int remainLivesMax = 3;						//１ステージの残機数
	int remainLives = 3;								//残機

	//ジャンプ
	const float jumpPowerMax = 8.0f;					//ジャンプパワー
	const float jumpBoxPowerMax = 9.0f;					//ジャンプ台のジャンプパワー
	bool jumpBoxFlag = false;							//ジャンプで箱を壊したか
	float jumpPower = 8.0f;								//ジャンプパワー
	float jumpPowerDelay = 0.2f;						//ジャンプパワー減衰
	float gravity = 5.0f;								//重力
	bool groundFlag = false;							//地面に接しているかどうか
	bool oldGroundFlag = false;							//地面に接していたかどうか
	bool blockStepOnFlag = false;						//ブロックを踏んで壊したかどうか

	//スピンステータス
	Box spinAttack = {};								//スピン箱
	const float spinScale = 10.0f;						//スピンの大きさ
	const int spinCoolTimeMax = 100;					//スピンのクールタイム最大
	int spinCoolTime = 0;								//スピンのクールタイム
	bool spinFlag = false;								//スピンをしたか

	//魚
	bool fishFlag = false;								//魚を獲得したか								
	int fishNum = 0;									//魚獲得数

	//プレイヤー演出
	Staging staging;									//演出クラス
	int dieNowTime = 0;									//死亡演出時間
	int dieType = DIENULL;								//死亡タイプ
	const int walkTimeMax = 5;							//歩くパーティクルを出す時間
	int walkTime = walkTimeMax;							//歩くパーティクルを出す時間最大

	//ステージ開始時の演出フラグ
	bool starStaging = false;
	const int startTimeMax = 60;
	int startTime = 0;

	//死亡時の情報
	const float fallPos = -30.0f;					//落下死の座標
	//魚死亡時
	Vec3 fishDiePos = {};
	Vec3 fishDieAngle = {};
	bool isFishDie = false;
	int decLifeTime = 0;

	//FBXクラス
	PlayerFBX pFbx;										
	//音データ
	int audioTime = 0;									//音を出す間隔
	SoundData walkSE = {};								//歩く音
	SoundData fallSE = {};								//落ちる音
	SoundData electSE = {};								//電気の音
};