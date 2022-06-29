#include"Player.h"
#include"Shape.h"
#include"Input.h"
#include"Collision.h"
Player::Player()
{}

Player::~Player()
{}

void Player::Init()
{
	//playerObject = Shape::CreateOBJ("player");
	playerObject = Shape::CreateOBJ("sphere");
	oldPosition = position;
	pSphere.radius = 7.0f;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
}

void Player::Update(Enemy* enemy)
{
	if (enemy == nullptr)
	{
		return;
	}
	oldPosition = position;
	vec = {};
	//�ړ�
	Move();
	//�W�����v
	Jump();

	position += vec;
	pSphere.center = XMVectorSet(position.x, position.y, position.z, 1);
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
	//������
	FallDie();
}

void Player::Draw()
{
	Object::Draw(playerObject, position, scale, angle, color);
#if _DEBUG

#endif

}

void Player::SetPosition(Vec3 position)
{
	this->position = position;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
}

void Player::GroundFlag()
{
	groundFlag = true;
}

void Player::Reset()
{
	position = { 90.0f,50.0f,10.0f };	//���W
	oldPosition = position;
}

//�ړ�
void Player::Move()
{
	//�ړ�
	if (Input::Instance()->KeybordPush(DIK_RIGHT))
	{
		vec.x += speed.x;
	}
	if (Input::Instance()->KeybordPush(DIK_LEFT))
	{
		vec.x -= speed.x;
	}
	if (Input::Instance()->KeybordPush(DIK_UP))
	{
		vec.z += speed.z;
	}
	if (Input::Instance()->KeybordPush(DIK_DOWN))
	{
		vec.z -= speed.z;
	}
}

void Player::Jump()
{
	//�W�����v
	if ((Input::Instance()->KeybordPush(DIK_SPACE) || blockStepOnFlag) && groundFlag == true)
	{
		jumpPower = jumpPowerMax;
		blockStepOnFlag = false;
	}


	//�d�͉��Z
	vec.y -= gravity;
	if (jumpPower > 0)
	{
		vec.y += jumpPower;
		jumpPower -= jumpPowerDelay;
	}
	groundFlag = false;
}

void Player::FallDie()
{
	//
	if (position.y < -30.0f)
	{
		Reset();
	}

}




