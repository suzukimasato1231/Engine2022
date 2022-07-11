#pragma once
#include"Player.h"
#include"Collision.h"
#include"Enemy.h"
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
	/// <summary>
	/// �v���C���[�Ɨ�����
	/// </summary>
	/// <param name="bPos"></param>
	/// <param name="bScale"></param>
	/// <param name="mapL"></param>
	/// <param name="mapR"></param>
	static int PlayerBox(Vec3 bPos, Vec3 bScale);
	/// <summary>
	/// �S�[���Ƃ̓����蔻��
	/// </summary>
	/// <param name="goalBox"></param>
	/// <returns></returns>
	static bool PlayerGoal(Box goalBox);


	static int PlayerBox2(WallData data1[4]);

	static int PlayerBreakBox(BreakBoxData data1[4],int &num);

	static bool Player2OBB(Vec3 bPos, Vec3 bScale);

};