#include"PushCollision.h"

void PushCollision::Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale)
{
	//��OBB�̓����蔻�艟���߂�����
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	while (1)
	{
		//�v���C���[OBB
		OBB pOBB;
		pOBB.Initilize(Vec3(Player::Instance()->GetPosition().x, Player::Instance()->GetPosition().y, Player::Instance()->GetPosition().z), Vec3{}, Player::Instance()->GetPSize());
		if (OBBCollision::ColOBBs(pOBB, diagonal))
		{
			Vec3 set = { Player::Instance()->GetPosition().x,Player::Instance()->GetPosition().y + 0.5f, Player::Instance()->GetPosition().z };
			Player::Instance()->SetPosition(set);
			Player::Instance()->GroundFlag();
		}
		else
		{
			break;
		}
	}
}

void PushCollision::PlayerBox(Vec3 bPos, Vec3 bScale)
{
	Box BlockBox = {};
	BlockBox.maxPosition = XMVectorSet(
		bPos.x + bScale.x / 2,
		bPos.y + bScale.y / 2,
		bPos.z + bScale.z / 2, 1);
	BlockBox.minPosition = XMVectorSet(
		bPos.x - bScale.x / 2,
		bPos.y - bScale.y / 2,
		bPos.z - bScale.z / 2, 1);
	Vec3 p = Player::Instance()->GetPosition();
	//�u���b�N�ƃv���C���[�̉����߂�����
	if (Collision::CheckBox2Box(Player::Instance()->GetBox(), BlockBox))
	{
		Vec3 set = Player::Instance()->GetPosition();
		//x
		float bL = bPos.x - bScale.x / 2;
		float bR = bPos.x + bScale.x / 2;
		//y
		float bD = bPos.y - bScale.y / 2;
		float bU = bPos.y + bScale.y / 2;
		//z
		float bz = bPos.z - bScale.z / 2;
		float b2z = bPos.z + bScale.z / 2;
		//x
		float pR = Player::Instance()->GetPosition().x + Player::Instance()->GetPSize().x;
		float pL = Player::Instance()->GetPosition().x - Player::Instance()->GetPSize().x;
		//y
		float pU = Player::Instance()->GetPosition().y + Player::Instance()->GetPSize().y;	
		float pD = Player::Instance()->GetPosition().y - Player::Instance()->GetPSize().y;
		//z	
		float pB = Player::Instance()->GetPosition().z + Player::Instance()->GetPSize().z;
		float pF = Player::Instance()->GetPosition().z - Player::Instance()->GetPSize().z;
		//�v���C���[���u���b�N���ォ����
		if (bU < Player::Instance()->GetOldPosition().y)
		{//��̎�
			if (bU > pD && bU < Player::Instance()->GetOldPosition().y)
			{
				set.y = bU + Player::Instance()->GetPSize().y / 2;
				Player::Instance()->GroundFlag();
			}
		}
		else
		{//���̎�
			if (bD < pU && bD>Player::Instance()->GetOldPosition().y)
			{
				set.y = bD - Player::Instance()->GetPSize().y / 2;
			}
		}
		//x
		if (bL < pR && bL > Player::Instance()->GetOldPosition().x)
		{
			set.x = bL - Player::Instance()->GetPSize().x / 2;
		}
		if (bR > pL && bR < Player::Instance()->GetOldPosition().x)
		{
			set.x = bR + Player::Instance()->GetPSize().x / 2;
		}
		//z
		if (bz < pB && bz>Player::Instance()->GetOldPosition().z)
		{
			set.z = bz - Player::Instance()->GetPSize().z / 2;
		}
		if (b2z > pF && b2z < Player::Instance()->GetOldPosition().z)
		{
			set.z = b2z + Player::Instance()->GetPSize().z / 2;
		}
		Player::Instance()->SetPosition(set);
	}

}

bool PushCollision::PlayerGoal(Box goalBox)
{
	//�u���b�N�ƃv���C���[�̉����߂�����
	if (Collision::CheckBox2Box(Player::Instance()->GetBox(), goalBox))
	{
		return true;
	}
	return false;
}


