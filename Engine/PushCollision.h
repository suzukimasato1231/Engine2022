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

	static void PlayerBox(Vec3 bPos, Vec3 bScale);

	static bool PlayerGoal(Box goalBox);
};