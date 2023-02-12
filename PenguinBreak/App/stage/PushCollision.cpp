#include"PushCollision.h"
#include<DirectXMath.h>
int PushCollision::Player2Floor(const Vec3 &pos, const Vec3 &angle, const Vec3 &scale, int moveFlag)
{
	//床OBBの当たり判定押し戻し処理
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	//プレイヤーOBB
	OBB eOBB;
	eOBB.Initilize(Vec3(Player::Get()->GetPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z), Vec3{}, Player::Get()->GetPSize());
	if (OBBCollision::ColOBBs(eOBB, diagonal))
	{
		while (1)
		{
			//プレイヤーOBB
			Vec3 set = {};
			eOBB.SetPos(Player::Get()->GetPosition());
			if (OBBCollision::ColOBBs(eOBB, diagonal))
			{
				diagonal.GetDirect(0);
				set = { Player::Get()->GetPosition().x,Player::Get()->GetPosition().y + 0.5f, Player::Get()->GetPosition().z };
				Player::Get()->SetPosition(set);
				Player::Get()->ActivateGround();
			}
			else
			{
				if (moveFlag == 0)
				{//動く床
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

int PushCollision::PlayerBreakBox(StageOBJ data1[4], int& num)
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

	const Vec3 oldPosition = Player::Get()->GetOldPosition();
	const Vec3 pSize = Player::Get()->GetPSize();
	const Vec3 vec = Player::Get()->GetVec();
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
			Player::Get()->ActivateGround();
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


	if (Flag[0] == true && Flag[1] == true && Flag[2] == true && BlockBox[1].maxPosition.m128_f32[0] == 0)
	{
		setPosition.x += vec.x;
		setPosition.y += vec.y;
	}
	else
	{
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
	}

	Player::Get()->SetPosition(setPosition);

	return breakFlag;
}
