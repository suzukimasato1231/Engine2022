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
	playerObject = Shape::CreateOBJ("pengin", true);
	oldPosition = position;
	pSphere.radius = 7.0f;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);

	playerFallDie.Init();
	////���f�������w�肵�ăt�@�C���ǂݍ���
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("pengin");
	////3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	//fbxObject1 = new FBXObject3d;
	//fbxObject1->Initialize();
	//fbxObject1->SetModel(model1);

	fishOBJ = Shape::CreateOBJ("fish", true);
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
	//���֘A
	Fish();
}

void Player::Draw(bool shadowFlag)
{
	Object::Draw(playerObject, psr, position, scale, angle, color, playerObject.OBJTexture, shadowFlag);
	////FBX����
	//fbxObject1->SetPosition(Vec3(position.x, position.y + 2.0f, position.z));
	//fbxObject1->SetRotation(angle);
	//fbxObject1->Update();
	//fbxObject1->Draw();
}

void Player::DrawParticle()
{
	playerFallDie.Draw();
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
	position = { 70.0f,25.0f,80.0f };	//���W
	oldPosition = position;
	remainLives = remainLivesMax;
	fishNum = 0;
	gameoverFlag = false;
}

//�ړ�
void Player::Move()
{
	if (dieType == DIENULL)
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
			angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)) - 59.8f);
		}
	}
}

void Player::Jump()
{
	//�W�����v
	if ((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA) || blockStepOnFlag)
		&& groundFlag == true)
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
	static const int dieTime = 30;	//���񂾂Ƃ��̉��o����

	if (position.y < -30.0f && dieType == DIENULL)
	{
		dieType = FALLDOWN;
		dieNowTime = dieTime;
		playerFallDie.Create(position);
	}

	if (dieType == FALLDOWN || dieType == ELECTDIE)
	{
		if (dieNowTime > 0)
		{
			dieNowTime--;
		}
		else if (remainLives > 0)
		{
			position = { 70.0f,20.0f,80.0f };	//���W
			oldPosition = position;
			remainLives--;
			dieType = DIENULL;
		}
		else if (remainLives == 0)
		{
			gameoverFlag = true;
			dieType = DIENULL;
		}
	}


	playerFallDie.Update();
}

void Player::Fish()
{
	if (changeBreakFlag == true)
	{
		fishFlag = true;
		changeBreakFlag = false;
	}
	if (fishFlag == true)
	{
		fishNum += 5;
		fishFlag = false;
	}

	//100�W�܂�����c�@�P������
	if (fishNum >= 100)
	{
		fishNum -= 100;
		remainLives++;
	}
}



