#pragma once
#include"../PenguinBreak/App/player/Player.h"
#include"Collision.h"
#include"Stage.h"
class PushCollision
{
public:
	/// <summary>
	/// 押し戻し処理
	/// </summary>
	/// <param name="stage">ステージクラス</param>
	/// <param name="player">プレイヤークラス</param>
	static int Player2Floor(const Vec3 &pos, const Vec3 &angle, const Vec3 &scale, int moveFlag = -1);

	static int PlayerBreakBox(StageOBJ data1[4], int& num);

};