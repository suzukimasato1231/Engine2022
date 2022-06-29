#pragma once
#include"Player.h"
#include"Collision.h"
#include"Enemy.h"
#include"Stage.h"
class PushCollision
{
public:
	/// <summary>
	/// 押し戻し処理
	/// </summary>
	/// <param name="stage">ステージクラス</param>
	/// <param name="player">プレイヤークラス</param>
	static void Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale);
	/// <summary>
	/// プレイヤーと立方体
	/// </summary>
	/// <param name="bPos"></param>
	/// <param name="bScale"></param>
	/// <param name="mapL"></param>
	/// <param name="mapR"></param>
	static int PlayerBox(Vec3 bPos, Vec3 bScale, int mapL, int mapR);
	/// <summary>
	/// ゴールとの当たり判定
	/// </summary>
	/// <param name="goalBox"></param>
	/// <returns></returns>
	static bool PlayerGoal(Box goalBox);
};