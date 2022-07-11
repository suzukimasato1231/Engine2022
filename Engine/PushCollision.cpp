#include"PushCollision.h"
#include<DirectXMath.h>
int PushCollision::Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale, int moveFlag)
{
	//��OBB�̓����蔻�艟���߂�����
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	//�v���C���[OBB
	OBB pOBB;
	pOBB.Initilize(Vec3(Player::Get()->GetPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z), Vec3{}, Player::Get()->GetPSize());
	if (OBBCollision::ColOBBs(pOBB, diagonal))
	{
		while (1)
		{
			//�v���C���[OBB
			Vec3 set = {};
			OBB pOBB;
			pOBB.Initilize(Vec3(Player::Get()->GetPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z), Vec3{}, Player::Get()->GetPSize());
			if (OBBCollision::ColOBBs(pOBB, diagonal))
			{
				diagonal.GetDirect(0);
				set = { Player::Get()->GetPosition().x,Player::Get()->GetPosition().y + 0.5f, Player::Get()->GetPosition().z };
				Player::Get()->SetPosition(set);
				Player::Get()->GroundFlag();
			}
			else
			{
				if (moveFlag == 0)
				{
					set = Player::Get()->GetPosition();
					set += Vec3(0.0f, 0.0f, 0.5f);
					Player::Get()->SetPosition(set);
				}
				else if (moveFlag == 1)
				{
					set = Player::Get()->GetPosition();
					set -= Vec3(0.0f, 0.0f, 0.5f);
					Player::Get()->SetPosition(set);
				}
				return 1;
			}
		}
	}
	return 0;
}

int PushCollision::PlayerBox(Vec3 bPos, Vec3 bScale)
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
	if (Collision::CheckBox2Box(Player::Get()->GetBox(), BlockBox))
	{
		Vec3 set = Player::Get()->GetPosition();
		//x
		float bL = bPos.x - bScale.x / 2, bR = bPos.x + bScale.x / 2;
		//y
		float bD = bPos.y - bScale.y / 2, bU = bPos.y + bScale.y / 2;
		//z
		float bz = bPos.z - bScale.z / 2, b2z = bPos.z + bScale.z / 2;
		//x
		float pR = Player::Get()->GetPosition().x + Player::Get()->GetPSize().x, pL = Player::Get()->GetPosition().x - Player::Get()->GetPSize().x;
		//y
		float pU = Player::Get()->GetPosition().y + Player::Get()->GetPSize().y, pD = Player::Get()->GetPosition().y - Player::Get()->GetPSize().y;
		//z	
		float pB = Player::Get()->GetPosition().z + Player::Get()->GetPSize().z, pF = Player::Get()->GetPosition().z - Player::Get()->GetPSize().z;
		//�����
		//��E
		if (bU > pD && bU < Player::Get()->GetOldPosition().y &&
			bR > pL && bR < Player::Get()->GetOldPosition().x)
		{
			set.x = bR + Player::Get()->GetPSize().x / 2 + 1.0f;
		}//�㍶
		else if (bU > pD && bU < Player::Get()->GetOldPosition().y &&
			bL < pR && bL > Player::Get()->GetOldPosition().x)
		{
			set.x = bL - Player::Get()->GetPSize().x / 2 - 1.0f;
		}//��O
		else if (bU > pD && bU < Player::Get()->GetOldPosition().y &&
			bz < pB && bz>Player::Get()->GetOldPosition().z)
		{
			set.z = bz - Player::Get()->GetPSize().z / 2 - 1.0f;
		}//�㉜
		else if (bU > pD && bU < Player::Get()->GetOldPosition().y &&
			b2z > pF && b2z < Player::Get()->GetOldPosition().z)
		{
			set.z = b2z + Player::Get()->GetPSize().z / 2 + 1.0f;
		}//���E
		else if (bD < pU && bD>Player::Get()->GetOldPosition().y &&
			bR > pL && bR < Player::Get()->GetOldPosition().x)
		{
			set.x = bR + Player::Get()->GetPSize().x / 2 + 1.0f;
		}//����
		else if (bD < pU && bD>Player::Get()->GetOldPosition().y &&
			bL < pR && bL > Player::Get()->GetOldPosition().x)
		{
			set.x = bL - Player::Get()->GetPSize().x / 2 - 1.0f;
		}
		//���O
		else if (bD < pU && bD>Player::Get()->GetOldPosition().y &&
			bz < pB && bz> Player::Get()->GetOldPosition().z)
		{
			set.z = bz - Player::Get()->GetPSize().z / 2 - 1.0f;
		}//����
		else if (bD < pU && bD>Player::Get()->GetOldPosition().y &&
			b2z > pF && b2z < Player::Get()->GetOldPosition().z)
		{
			set.z = b2z + Player::Get()->GetPSize().z / 2 + 1.0f;
		}
		//�E��
		else if (bR > pL && bR < Player::Get()->GetOldPosition().x &&
			b2z > pF && b2z < Player::Get()->GetOldPosition().z)
		{
			if (bR < Player::Get()->GetOldPosition().x - Player::Get()->GetPSize().x)
			{
				set.x = bR + Player::Get()->GetPSize().x / 2 + 1.0f;
			}
			else
			{
				set.z = b2z + Player::Get()->GetPSize().z / 2 + 1.0f;
			}
		}
		//����
		else if (bL < pR && bL > Player::Get()->GetOldPosition().x &&
			b2z > pF && b2z < Player::Get()->GetOldPosition().z)
		{
			if (bL > Player::Get()->GetOldPosition().x + Player::Get()->GetPSize().x)
			{
				set.x = bL - Player::Get()->GetPSize().x / 2 - 1.0f;
			}
			else
			{
				set.z = b2z + Player::Get()->GetPSize().z / 2 + 1.0f;
			}
		}//�E�O
		else if (bR > pL && bR < Player::Get()->GetOldPosition().x &&
			bz < pB && bz>Player::Get()->GetOldPosition().z)
		{
			if (bR < Player::Get()->GetOldPosition().x + Player::Get()->GetPSize().x)
			{
				set.x = bR + Player::Get()->GetPSize().x / 2 + 1.0f;
			}
			else
			{
				set.z = bz - Player::Get()->GetPSize().z / 2 - 1.0f;
			}
		}//���O
		else if (bL < pR && bL > Player::Get()->GetOldPosition().x &&
			bz < pB && bz>Player::Get()->GetOldPosition().z)
		{
			if (bL > Player::Get()->GetOldPosition().x - Player::Get()->GetPSize().x)
			{
				set.x = bL - Player::Get()->GetPSize().x / 2 - 1.0f;
			}
			else
			{
				set.z = bz - Player::Get()->GetPSize().z / 2 - 1.0f;
			}
		}
		else
		{//�����		
			//��̎�
			if (bU > pD && bU < Player::Get()->GetOldPosition().y)
			{
				set.y = bU + Player::Get()->GetPSize().y / 2 + 1.0f;
				Player::Get()->GroundFlag();
				Flag = 1;
			}
			//���̎�
			if (bD < pU && bD>Player::Get()->GetOldPosition().y)
			{
				set.y = bD - Player::Get()->GetPSize().y / 2 - 1.0f;
				Flag = 2;
			}
			//x
			if (bL < pR && bL > Player::Get()->GetOldPosition().x)
			{
				set.x = bL - Player::Get()->GetPSize().x / 2 - 1.0f;
			}
			if (bR > pL && bR < Player::Get()->GetOldPosition().x)
			{
				set.x = bR + Player::Get()->GetPSize().x / 2 + 1.0f;
			}
			//z
			if (bz < pB && bz>Player::Get()->GetOldPosition().z)
			{
				set.z = bz - Player::Get()->GetPSize().z / 2 - 1.0f;
			}
			if (b2z > pF && b2z < Player::Get()->GetOldPosition().z)
			{
				set.z = b2z + Player::Get()->GetPSize().z / 2 + 1.0f;
			}
		}
		Player::Get()->SetPosition(set);
	}
	return Flag;
}

bool PushCollision::PlayerGoal(Box goalBox)
{
	//�u���b�N�ƃv���C���[�̉����߂�����
	if (Collision::CheckBox2Box(Player::Get()->GetBox(), goalBox))
	{
		return true;
	}
	return false;
}



int PushCollision::PlayerBox2(WallData data1[4])
{
	Box BlockBox[4] = {};
	Box pBox = {};
	for (int i = 0; i < 4; i++)
	{
		BlockBox[i].maxPosition = XMVectorSet(
			data1[i].position.x + data1[i].scale.x / 2,
			data1[i].position.y + data1[i].scale.y / 2,
			data1[i].position.z + data1[i].scale.z / 2, 1);
		BlockBox[i].minPosition = XMVectorSet(
			data1[i].position.x - data1[i].scale.x / 2,
			data1[i].position.y - data1[i].scale.y / 2,
			data1[i].position.z - data1[i].scale.z / 2, 1);
	}

	Vec3 oldPosition = Player::Get()->GetOldPosition();
	Vec3 pSize = Player::Get()->GetPSize();
	Vec3 vec = Player::Get()->GetVec();
	bool Flag[3] = {};


	Vec3 result = Vec3(oldPosition.x + vec.x, oldPosition.y, oldPosition.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[0] = true;
		}
	}

	result = Vec3(oldPosition.x, oldPosition.y + vec.y, oldPosition.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[1] = true;
			Player::Get()->GroundFlag();
		}
	}

	result = Vec3(oldPosition.x, oldPosition.y, oldPosition.z + vec.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[2] = true;
		}
	}

	Vec3 setPosition = oldPosition;
	if (Flag[0] == false)
	{
		setPosition.x += vec.x;
	}
	if (Flag[1] == false)
	{
		setPosition.y += vec.y;
	}
	if (Flag[2] == false)
	{
		setPosition.z += vec.z;
	}


	Player::Get()->SetPosition(setPosition);
	return 0;
}


int PushCollision::PlayerBreakBox(BreakBoxData data1[4], int& num)
{
	int breakFlag = 0;
	Box BlockBox[4] = {};
	Box pBox = {};
	for (int i = 0; i < 4; i++)
	{
		BlockBox[i].maxPosition = XMVectorSet(
			data1[i].position.x + data1[i].scale.x / 2,
			data1[i].position.y + data1[i].scale.y / 2,
			data1[i].position.z + data1[i].scale.z / 2, 1);
		BlockBox[i].minPosition = XMVectorSet(
			data1[i].position.x - data1[i].scale.x / 2,
			data1[i].position.y - data1[i].scale.y / 2,
			data1[i].position.z - data1[i].scale.z / 2, 1);
	}

	Vec3 oldPosition = Player::Get()->GetOldPosition();
	Vec3 pSize = Player::Get()->GetPSize();
	Vec3 vec = Player::Get()->GetVec();
	bool Flag[3] = {};


	Vec3 result = Vec3(oldPosition.x + vec.x, oldPosition.y, oldPosition.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[0] = true;
		}
	}

	result = Vec3(oldPosition.x, oldPosition.y + vec.y, oldPosition.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[1] = true;
			Player::Get()->GroundFlag();
			if (vec.y < 0)
			{
				breakFlag = 1;
				num = i;
			}
			else
			{
				breakFlag = 2;
				num = i;
			}

		}
	}

	result = Vec3(oldPosition.x, oldPosition.y, oldPosition.z + vec.z);
	pBox.maxPosition = XMVectorSet(result.x + pSize.x / 2, result.y + pSize.y / 2, result.z + pSize.z / 2, 1);
	pBox.minPosition = XMVectorSet(result.x - pSize.x / 2, result.y - pSize.y / 2, result.z - pSize.z / 2, 1);
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CheckBox2Box(pBox, BlockBox[i]))
		{
			Flag[2] = true;
		}
	}

	Vec3 setPosition = oldPosition;
	if (Flag[0] == false)
	{
		setPosition.x += vec.x;
	}
	if (Flag[1] == false)
	{
		setPosition.y += vec.y;
	}
	if (Flag[2] == false)
	{
		setPosition.z += vec.z;
	}
	Player::Get()->SetPosition(setPosition);

	return breakFlag;
}





/// <summary>
/// 
/// </summary>
/// <param name="front">�i�s�x�N�g��</param>
/// <param name="normal">�Փ˓_�ł̖@���x�N�g��</param>
/// <returns></returns>
XMVECTOR calcWallScratchVector(const XMVECTOR front, const XMVECTOR normal);


bool PushCollision::Player2OBB(Vec3 bPos, Vec3 bScale)
{
	//�E����
	//�E���O
	Vec3 A = Vec3(bPos.x - bScale.x / 2, bPos.y - bScale.y / 2, bPos.z - bScale.z / 2);
	Vec3 B = Vec3(bPos.x - bScale.x / 2, bPos.y - bScale.y / 2, bPos.z + bScale.z / 2);
	Vec3 C = Vec3(bPos.x - bScale.x / 2, bPos.y + bScale.y / 2, bPos.z - bScale.z / 2);
	//AB�̃x�N�g��
	Vec3 AB = B - A;
	Vec3 BC = C - B;
	//�E�ӂ̖@���x�N�g��
	Vec3 ABC = AB.cross(BC);

	Vec3 ABCnormal = ABC.normalize();

	XMVECTOR abc = XMVectorSet(1, 0, 0, 1);

	////��
	////�E���O
	//Vec3 D = Vec3(bPos.x + bScale.x / 2, bPos.y - bScale.y / 2, bPos.z + bScale.z / 2);
	//Vec3 E = Vec3(bPos.x - bScale.x / 2, bPos.y - bScale.y / 2, bPos.z + bScale.z / 2);
	//Vec3 F = Vec3(bPos.x + bScale.x / 2, bPos.y + bScale.y / 2, bPos.z + bScale.z / 2);
	////AB�̃x�N�g��
	//Vec3 DE = E - D;
	//Vec3 DF = F - D;
	////�E�ӂ̖@���x�N�g��
	//Vec3 DEF = DE.cross(DF);



	//�v���C�C���[�x�N�g��
	XMVECTOR MoveVector = XMVectorSet(
		Player::Get()->GetVec().x,
		0.0f,
		Player::Get()->GetVec().z, 1);
	//�E���������߂�����

	Box BlockBox = {};
	BlockBox.maxPosition = XMVectorSet(
		bPos.x + bScale.x / 2,
		bPos.y + bScale.y / 2,
		bPos.z + bScale.z / 2, 1);
	BlockBox.minPosition = XMVectorSet(
		bPos.x - bScale.x / 2,
		bPos.y - bScale.y / 2,
		bPos.z - bScale.z / 2, 1);

	XMVECTOR add = {};
	//�u���b�N�ƃv���C���[�̉����߂�����
	if (Collision::CheckBox2Box(Player::Get()->GetBox(), BlockBox))
	{
		add = calcWallScratchVector(MoveVector, abc);
		add *= 3.0f;
	}
	Player::Get()->SetPosition(Vec3(add.m128_f32[0], add.m128_f32[1], add.m128_f32[2]) + Player::Get()->GetPosition());
	return 0;
}


//�Փ˓_�̋��߂���

//�@���x�N�g��

//�i�s�x�N�g��

//���˃x�N�g�������߂�
XMVECTOR calcWallScratchVector(const XMVECTOR front, const XMVECTOR normal)
{
	XMVECTOR normal_n;
	normal_n = XMVector3Normalize(normal);
	return XMVector3Normalize(front - XMVector3Dot(front, normal_n) * normal_n);
}