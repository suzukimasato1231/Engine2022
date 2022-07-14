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
	static int Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale, int moveFlag = -1);

	static int PlayerBreakBox(StageOBJ data1[4],int &num);

	static bool Player2OBB(Vec3 bPos, Vec3 bScale);

};