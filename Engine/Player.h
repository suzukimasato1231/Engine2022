#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"

class Enemy;

class Player :public Singleton<Player>
{
public:
	friend Singleton<Player>;
public:
	Player();//コンストラクタ

	~Player();//ですコンストラクタ

	void Init();//初期化

	void Update(class Enemy *enemy);//更新

	void Draw();//描画

	void SetPosition(Vec3 position);
	/// <summary>
	/// trueにする
	/// </summary>
	void GroundFlag();

	void Reset();
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
public://取得系
	//座標
	Vec3 GetPosition() { return position; }

	Vec3 GetOldPosition() { return oldPosition; }

	Vec3 GetPSize() { return pScale; }

	Sphere GetSphere() { return pSphere; }

	Box GetBox() { return pBox; }

	Vec3 GetVec() { return vec; }

	float GetJumpPower() { return jumpPower; }
private:
	ObjectData playerObject;			//プレイヤーオブジェクト
	Vec3 position{ 10.0f,20.0f,0.0f };	//座標
	Vec3 oldPosition{};					//1つ前の座標
	Vec3 speed{ 2.0f,2.0f,2.0f };		//プレイヤースピード
	Vec3 scale{ 4.0f,4.0f,4.0f };		//大きさ
	Vec3 angle{ 0.0f,0.0f,0.0f };		//角度
	Vec4 color{ 1.0f,1.0f,1.0f,1.0f };	//色
	Vec3 pScale = { 5.0f,7.0f,5.0f };	//プレイヤー大きさ
	Sphere pSphere;						//プレイヤーの球
	Box pBox;							//プレイヤーの箱
	int HP = 10;						//プレイヤーHP


	Vec3 vec = {};						

	//ジャンプ
	const float jumpPowerMax = 8.0f;
	float jumpPower = 8.0f;//ジャンプパワー
	float jumpPowerDelay = 0.2f;
	float gravity = 5.0f;//重力
	bool groundFlag = false;//地面に接しているかどうか
};