#include"PushCollision.h"

int PushCollision::Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale, int moveFlag)
{
	//��OBB�̓����蔻�艟���߂�����
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	//�v���C���[OBB
	OBB pOBB;
	pOBB.Initilize(Vec3(Player::Instance()->GetPosition().x, Player::Instance()->GetPosition().y, Player::Instance()->GetPosition().z), Vec3{}, Player::Instance()->GetPSize());
	if (OBBCollision::ColOBBs(pOBB, diagonal))
	{
		while (1)
		{
			//�v���C���[OBB
			Vec3 set = {};
			OBB pOBB;
			pOBB.Initilize(Vec3(Player::Instance()->GetPosition().x, Player::Instance()->GetPosition().y, Player::Instance()->GetPosition().z), Vec3{}, Player::Instance()->GetPSize());
			if (OBBCollision::ColOBBs(pOBB, diagonal))
			{
				set = { Player::Instance()->GetPosition().x,Player::Instance()->GetPosition().y + 0.5f, Player::Instance()->GetPosition().z };
				Player::Instance()->SetPosition(set);
				Player::Instance()->GroundFlag();
			}
			else
			{
				if (moveFlag == 0)
				{
					set = Player::Instance()->GetPosition();
					set += Vec3(0.0f, 0.0f, 0.5f);
					Player::Instance()->SetPosition(set);
				}
				else if (moveFlag == 1)
				{
					set = Player::Instance()->GetPosition();
					set -= Vec3(0.0f, 0.0f, 0.5f);
					Player::Instance()->SetPosition(set);
				}
				return 1;
			}
		}
	}
	return 0;
}

int PushCollision::PlayerBox(Vec3 bPos, Vec3 bScale, int mapL, int mapR)
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
	int Flag = false;
	//�u���b�N�ƃv���C���[�̉����߂�����
	if (Collision::CheckBox2Box(Player::Instance()->GetBox(), BlockBox))
	{
		Vec3 set = Player::Instance()->GetPosition();
		//x
		float bL = bPos.x - bScale.x / 2, bR = bPos.x + bScale.x / 2;
		//y
		float bD = bPos.y - bScale.y / 2, bU = bPos.y + bScale.y / 2;
		//z
		float bz = bPos.z - bScale.z / 2, b2z = bPos.z + bScale.z / 2;
		//x
		float pR = Player::Instance()->GetPosition().x + Player::Instance()->GetPSize().x, pL = Player::Instance()->GetPosition().x - Player::Instance()->GetPSize().x;
		//y
		float pU = Player::Instance()->GetPosition().y + Player::Instance()->GetPSize().y, pD = Player::Instance()->GetPosition().y - Player::Instance()->GetPSize().y;
		//z	
		float pB = Player::Instance()->GetPosition().z + Player::Instance()->GetPSize().z, pF = Player::Instance()->GetPosition().z - Player::Instance()->GetPSize().z;
		//�����
		//��E
		if (bU > pD && bU < Player::Instance()->GetOldPosition().y &&
			bR > pL && bR < Player::Instance()->GetOldPosition().x)
		{
			set.x = bR + Player::Instance()->GetPSize().x / 2;
		}//�㍶
		else if (bU > pD && bU < Player::Instance()->GetOldPosition().y &&
			bL < pR && bL > Player::Instance()->GetOldPosition().x)
		{
			set.x = bL - Player::Instance()->GetPSize().x / 2;
		}//��O
		else if (bU > pD && bU < Player::Instance()->GetOldPosition().y &&
			bz < pB && bz>Player::Instance()->GetOldPosition().z)
		{
			set.z = bz - Player::Instance()->GetPSize().z / 2;
		}//�㉜
		else if (bU > pD && bU < Player::Instance()->GetOldPosition().y &&
			b2z > pF && b2z < Player::Instance()->GetOldPosition().z)
		{
			set.z = b2z + Player::Instance()->GetPSize().z / 2;
		}//���E
		else if (bD < pU && bD>Player::Instance()->GetOldPosition().y &&
			bR > pL && bR < Player::Instance()->GetOldPosition().x)
		{
			set.x = bR + Player::Instance()->GetPSize().x / 2;
		}//����
		else if (bD < pU && bD>Player::Instance()->GetOldPosition().y &&
			bL < pR && bL > Player::Instance()->GetOldPosition().x)
		{
			set.x = bL - Player::Instance()->GetPSize().x / 2;
		}
		//���O
		else if (bD < pU && bD>Player::Instance()->GetOldPosition().y &&
			bz < pB && bz> Player::Instance()->GetOldPosition().z)
		{
			set.z = bz - Player::Instance()->GetPSize().z / 2;
		}//����
		else if (bD < pU && bD>Player::Instance()->GetOldPosition().y &&
			b2z > pF && b2z < Player::Instance()->GetOldPosition().z)
		{
			set.z = b2z + Player::Instance()->GetPSize().z / 2;
		}
		//�E��
		else if (bR > pL && bR < Player::Instance()->GetOldPosition().x &&
			b2z > pF && b2z < Player::Instance()->GetOldPosition().z)
		{
			if (mapL > 0)
			{
				set.x = bR + Player::Instance()->GetPSize().x / 2;
			}
			else
			{
				set.z = b2z + Player::Instance()->GetPSize().z / 2;
			}
		}
		//����
		else if (bL < pR && bL > Player::Instance()->GetOldPosition().x &&
			b2z > pF && b2z < Player::Instance()->GetOldPosition().z)
		{
			if (mapR > 0)
			{
				set.x = bL - Player::Instance()->GetPSize().x / 2;
			}
			else
			{
				set.z = b2z + Player::Instance()->GetPSize().z / 2;
			}
		}//�E�O
		else if (bR > pL && bR < Player::Instance()->GetOldPosition().x &&
			bz < pB && bz>Player::Instance()->GetOldPosition().z)
		{
			if (mapL > 0)
			{
				set.x = bR + Player::Instance()->GetPSize().x / 2;
			}
			else
			{
				set.z = bz - Player::Instance()->GetPSize().z / 2;
			}
		}//���O
		else if (bL < pR && bL > Player::Instance()->GetOldPosition().x &&
			bz < pB && bz>Player::Instance()->GetOldPosition().z)
		{
			if (mapR > 0)
			{
				set.x = bL - Player::Instance()->GetPSize().x / 2;
			}
			else
			{
				set.z = bz - Player::Instance()->GetPSize().z / 2;
			}
		}
		else
		{//�����		
			//��̎�
			if (bU > pD && bU < Player::Instance()->GetOldPosition().y)
			{
				set.y = bU + Player::Instance()->GetPSize().y / 2;
				Player::Instance()->GroundFlag();
				Flag = 1;
			}
			//���̎�
			if (bD < pU && bD>Player::Instance()->GetOldPosition().y)
			{
				set.y = bD - Player::Instance()->GetPSize().y / 2;
				Flag = 2;
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
		}
		Player::Instance()->SetPosition(set);
	}
	return Flag;
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


