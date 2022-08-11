#include"Player.h"
#include"Shape.h"
#include"Input.h"
#include"Collision.h"
#include "Safe_delete.h"
Player::Player()
{}

Player::~Player()
{
	safe_delete(fbxObject1);
	safe_delete(model1);
}

void Player::Init()
{
	playerObject = Shape::CreateOBJ("player", true);
	oldPosition = position;
	pSphere.radius = 7.0f;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
	//���f�������w�肵�ăt�@�C���ǂݍ���
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("Player2");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	fbxObject1 = new FBXObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(model1);
}

void Player::Update()
{
	oldPosition = position;
	oldGroundFlag = groundFlag;
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

void Player::Draw(bool shadowFlag)
{
	Object::Draw(playerObject, position, scale, angle, color, playerObject.OBJTexture, shadowFlag);
	////FBX����
	//fbxObject1->SetPosition(Vec3(position.x, position.y + 2.0f, position.z));
	//fbxObject1->SetRotation(angle);
	//fbxObject1->Update();
	//fbxObject1->Draw();
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
	position = { 70.0f,20.0f,80.0f };	//���W
	oldPosition = position;
}

//�ړ�
void Player::Move()
{
	if (moveFlag == true)
	{
		if (Input::Get()->KeybordPush(DIK_UP))
		{
			vec.z += speed.z;
		}
		if (Input::Get()->KeybordPush(DIK_DOWN))
		{
			vec.z -= speed.z;
		}
	}
	//�ړ�
	if (Input::Get()->KeybordPush(DIK_RIGHT))
	{
		vec.x += speed.x;
	}
	if (Input::Get()->KeybordPush(DIK_LEFT))
	{
		vec.x -= speed.x;
	}
	//�R���g���[���[�ړ�
	if (Input::Get()->ConLeftInput())
	{
		float rad = Input::Get()->GetLeftAngle();
		vec.x = speed.x * sinf(-rad);
		if (moveFlag == true)
		{
			vec.z = speed.z * cosf(rad);
		}
		angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad))) - 90;
	}
}

void Player::Jump()
{
	//�W�����v
	if ((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA) || blockStepOnFlag) && groundFlag == true)
	{
		if (jumpBoxFlag)
		{
			jumpPower = jumpBoxPowerMax;
			jumpBoxFlag = false;
		}
		else
		{
			jumpPower = jumpPowerMax;
		}
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
	if (position.y < -30.0f)
	{
		Reset();
	}
}




