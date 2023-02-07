#pragma once
#include"../PenguinBreak/App/player/Player.h"
#include"Collision.h"
#include"Stage.h"
class PushCollision
{
public:
	/// <summary>
	/// �����߂�����
	/// </summary>
	/// <param name="stage">�X�e�[�W�N���X</param>
	/// <param name="player">�v���C���[�N���X</param>
	static int Player2Floor(const Vec3 &pos, const Vec3 &angle, const Vec3 &scale, int moveFlag = -1);

	static int PlayerBreakBox(StageOBJ data1[4], int& num);

};