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
enum class DieType
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
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
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
	void ActivateGround() { m_groundFlag = true; }
	/// <summary>
	/// 値リセット
	/// </summary>
	void Reset();
	/// <summary>
	///　箱をジャンプで壊したか
	/// </summary>
	void ActivateBlockStepOn() { m_blockStepOnFlag = true; }
	/// <summary>
	/// ジャンプ力をゼロにする
	/// </summary>
	void JumpPoweZero() { m_jumpPower = 0; }
	/// <summary>
	/// 2D false 3D true　
	/// </summary>
	/// <param name="moveFlag">2Dか3Dのフラグ</param>
	void SetMoveFlag(bool moveFlag) { m_moveFlag = moveFlag; }
	/// <summary>
	/// ジャンプ箱を踏んだか
	/// </summary>
	void ActivateJumpBox() { m_jumpBoxFlag = true; }
	/// <summary>
	/// 箱を壊したか
	/// </summary>
	void ActivateChangeBreak() { m_changeBreakFlag = true; }

	void DieType(int type) { if (m_dieType != static_cast<int>(DieType::DIENOW)) { m_dieType = type; } }

	void FishDie(const Vec3& pos, const Vec3& angle) { m_fishDiePos = pos, m_fishDieAngle, angle; }
	//ゴール時の演出
	void GoalStaging(int fbxType);

	void GetClearFlag(bool clearFlag) { m_clearFlag = clearFlag; }

	int GetDecLifeFlag() { return m_decLifeTime; }

	void StopAnimation();
private:
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
	/// <summary>
	/// 落下したか
	/// </summary>
	/// <param name="pos">プレイヤー位置</param>
	/// <returns></returns>
	bool OutofFallDown(const Vec3& pos);
public://取得系
	inline Vec3 GetPosition() { return m_position; }

	inline Vec3 GetOldPosition() { return m_oldPosition; }

	inline Vec3 GetPSize() { return m_pScale; }

	inline Box GetBox() { return m_pBox; }

	inline Vec3 GetVec() { return m_vec; }

	inline float GetJumpPower() { return m_jumpPower; }

	inline bool GetGroundFlag() { return m_groundFlag; }

	inline bool GetOldGroundFlag() { return m_oldGroundFlag; }
	
	inline int GetRemanLives() { return m_remainLives; }

	inline int GetFishNum() { return m_fishNum; }

	inline bool GetGameoverFlag() { return m_gameoverFlag; }

	inline bool GetIsFishDie() { return m_isFishDie; }

	inline Box GetSpinBox() { return m_spinAttack; }

	inline bool GetSpinFlag() { return m_spinFlag; }
private:
	//ゲームフラグ
	bool m_moveFlag = false;								//2D false 3D true
	bool m_gameoverFlag = false;							//ゲームオーバーかどうか
	bool m_clearFlag = false;								//クリアしたかどうか
	//プレイヤーステータス
	ObjectData m_playerObject;							//プレイヤーオブジェクト
	PSR m_psr = {};										//プレイヤーの位置座標大きさ保存用
	Vec3 m_position = { 94.0f,14.0f,80.0f };				//座標
	const Vec3 c_firstPosition = { 90.0f,25.0f,80.0f };	//初期位置
	Vec3 m_oldPosition = {};								//1つ前の座標
	const Vec3 c_speed = { 2.0f,2.0f,2.0f };				//走るスピード
	const Vec3 c_walkSpeed = { 1.0f,1.0f,1.0f };			//歩くスピード
	Vec3 m_angle = { -30.0f,180.0f,0.0f };				//角度
	const Vec3 c_firstAngle = { -30.0f,180.0f,0.0f };		//最初の角度
	Vec3 m_pScale = { 12.0f,5.0f,12.0f };					//プレイヤーの大きさ
	Box m_pBox;											//プレイヤーBOX
	Vec3 m_vec = {};
	bool m_changeBreakFlag = false;

	const int c_remainLivesMax = 3;						//１ステージの残機数
	int m_remainLives = 3;								//残機

	//ジャンプ
	const float c_jumpPowerMax = 8.0f;					//ジャンプパワー
	const float c_jumpBoxPowerMax = 9.0f;					//ジャンプ台のジャンプパワー
	bool m_jumpBoxFlag = false;							//ジャンプで箱を壊したか
	float m_jumpPower = 8.0f;								//ジャンプパワー
	float m_jumpPowerDelay = 0.2f;						//ジャンプパワー減衰
	float m_gravity = 5.0f;								//重力
	bool m_groundFlag = false;							//地面に接しているかどうか
	bool m_oldGroundFlag = false;							//地面に接していたかどうか
	bool m_blockStepOnFlag = false;						//ブロックを踏んで壊したかどうか

	//スピンステータス
	Box m_spinAttack = {};								//スピン箱
	const float c_spinScale = 10.0f;						//スピンの大きさ
	const int c_spinCoolTimeMax = 100;					//スピンのクールタイム最大
	int m_spinCoolTime = 0;								//スピンのクールタイム
	bool m_spinFlag = false;								//スピンをしたか

	//魚
	bool m_fishFlag = false;								//魚を獲得したか								
	int m_fishNum = 0;									//魚獲得数
	const int c_fishMax = 100;							//最大獲得数
	const int c_fishPlas = 5;								//一回の獲得数

	//プレイヤー演出
	Staging m_staging;									//演出クラス
	int m_dieNowTime = 0;									//死亡演出時間
	int m_dieType = static_cast<int>(DieType::DIENULL);								//死亡タイプ
	const int c_walkTimeMax = 5;							//歩くパーティクルを出す時間
	int m_walkTime = c_walkTimeMax;							//歩くパーティクルを出す時間最大

	//ステージ開始時の演出フラグ
	bool m_starStaging = false;
	const int c_startTimeMax = 60;
	int m_startTime = 0;

	//死亡時の情報
	const float c_fallPos = -30.0f;						//落下死の座標
	//魚死亡時
	Vec3 m_fishDiePos = {};
	Vec3 m_fishDieAngle = {};
	bool m_isFishDie = false;
	int m_decLifeTime = 0;

	//FBXクラス
	PlayerFBX m_pFbx;
	//音データ
	int m_audioTime = 0;									//音を出す間隔
	SoundData m_walkSE = {};								//歩く音
	SoundData m_fallSE = {};								//落ちる音
	SoundData m_electSE = {};								//電気の音
};