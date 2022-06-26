#include"PushCollision.h"

void PushCollision::Player2Floor(Vec3 pos, Vec3 angle, Vec3 scale)
{
	//床OBBの当たり判定押し戻し処理
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	while (1)
	{
		//プレイヤーOBB
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
	//ブロックとプレイヤーの押し戻し処理
	if (Collision::CheckBox2Box(Player::Instance()->GetBox(), BlockBox))
	{
		Vec3 set = Player::Instance()->GetPosition();
		//x
		float bL = bPos.x - bScale.x / 2;
		float bR = bPos.x + bScale.x / 2;
		//y
		float b = bPos.y - bScale.y / 2;
		float b2 = bPos.y + bScale.y / 2;
		//z
		float bz = bPos.z - bScale.z / 2;
		float b2z = bPos.z + bScale.z / 2;
		//x
		float pR = Player::Instance()->GetPosition().x + Player::Instance()->GetPSize().x;
		float pL = Player::Instance()->GetPosition().x - Player::Instance()->GetPSize().x;
		//y
		float p = Player::Instance()->GetPosition().y + Player::Instance()->GetPSize().y;	
		float p2 = Player::Instance()->GetPosition().y - Player::Instance()->GetPSize().y;
		//z	
		float pz = Player::Instance()->GetPosition().z + Player::Instance()->GetPSize().z;
		float p2z = Player::Instance()->GetPosition().z - Player::Instance()->GetPSize().z;
		//プレイヤーがブロックより上か下か
		if (b2 < Player::Instance()->GetOldPosition().y)
		{//上の時
			if (b2 > p2 && b2 < Player::Instance()->GetOldPosition().y)
			{
				set.y = b2 + Player::Instance()->GetPSize().y / 2;
				Player::Instance()->GroundFlag();
			}
		}
		else
		{//下の時
			if (b < p && b>Player::Instance()->GetOldPosition().y)
			{
				set.y = b - Player::Instance()->GetPSize().y / 2;
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
		if (bz < pz && bz>Player::Instance()->GetOldPosition().z)
		{
			set.z = bz - Player::Instance()->GetPSize().z / 2;
		}
		if (b2z > p2z && b2z < Player::Instance()->GetOldPosition().z)
		{
			set.z = b2z + Player::Instance()->GetPSize().z / 2;
		}
		Player::Instance()->SetPosition(set);
	}

}


