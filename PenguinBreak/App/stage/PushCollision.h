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
	static int Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale, int moveFlag = -1);

	static int PlayerBreakBox(StageOBJ data1[4], int& num);

};