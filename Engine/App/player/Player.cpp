#include"Player.h"
#include"Shape.h"
#include"Input.h"
#include"Collision.h"
#include "Safe_delete.h"
Player::Player()
{}

Player::~Player()
{}

void Player::Init()
{
	playerObject = Shape::CreateOBJ("pengin", true);
	oldPosition = position;
	pSphere.radius = 7.0f;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);

	staging.Init();
	//���f�������w�肵�ăt�@�C���ǂݍ���
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("pengin2");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	fbxObject1 = new FBXObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(model1);

	//���f�������w�肵�ăt�@�C���ǂݍ���
	stopModel = FbxLoader::GetInstance()->LoadModelFromFile("movePengin");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	stopFbx = new FBXObject3d;
	stopFbx->Initialize();
	stopFbx->SetModel(stopModel);
	///////////////////
	//���f�������w�肵�ăt�@�C���ǂݍ���
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("pengin2");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	fbxObject2 = new FBXObject3d;
	fbxObject2->Initialize();
	fbxObject2->SetModel(model2);

	//���f�������w�肵�ăt�@�C���ǂݍ���
	stopModel2 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin");
	//3D�I�u�W�F�N�g�̐����ƃ��f���̃Z�b�g
	stopFbx2 = new FBXObject3d;
	stopFbx2->Initialize();
	stopFbx2->SetModel(stopModel2);
	//////////////////////////
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
	//Object::Draw(playerObject, psr, Vec3(position.x, position.y - 2.0f, position.z), scale, angle, Vec4(), playerObject.OBJTexture, shadowFlag);
	staging.Draw3D();

	FbxDraw(shadowFlag);

	Object::Get()->PreDraw(shadowFlag);
}

void Player::DrawParticle()
{
	staging.Draw();
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

void Player::Delete()
{
	safe_delete(fbxObject1);
	safe_delete(model1);
	safe_delete(stopFbx);
	safe_delete(stopModel);
}

void Player::FbxDraw(bool shadowFlag)
{
	Vec3 fbxPos = { position.x, position.y - 2.0f, position.z };
	//FBX����
	switch (fbxType)
	{
	case None:
		stopFbx->SetPosition(fbxPos);
		stopFbx->SetRotation(angle);
		stopFbx2->SetPosition(fbxPos);
		stopFbx2->SetRotation(angle);


		stopFbx->Update(shadowFlag);
		stopFbx2->Update(false);
		break;
	case Walk:
		fbxObject1->SetPosition(fbxPos);
		fbxObject1->SetRotation(angle);
		fbxObject2->SetPosition(fbxPos);
		fbxObject2->SetRotation(angle);


		fbxObject1->Update(shadowFlag);
		fbxObject2->Update(false);
		break;
	default:
		break;
	}
	switch (fbxType)
	{
	case None:
		if (shadowFlag == false)
		{
			stopFbx->Draw();
		}
		else
		{
			stopFbx2->Draw();
		}
		break;
	case Walk:
		if (shadowFlag == false)
		{
			fbxObject1->Draw();
		}
		else
		{
			fbxObject2->Draw();
		}
		break;
	default:
		break;
	}
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
			angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));// -59.8f);
			if (walkTime < 0)
			{
				staging.CreateWalk(position, vec);
				walkTime = walkTimeMax;
			}
			walkTime--;


			if (fbxFlag[0] == false)
			{//�A�j���[�V�����J�n
				stopFbx->StopAnimation();
				stopFbx2->StopAnimation();
				fbxObject1->PlayAnimation(true);
				fbxObject2->PlayAnimation(true);
				fbxFlag[0] = true;
			}
			fbxFlag[1] = false;
			fbxType = Walk;
		}
		else
		{
			fbxType = None;
			fbxFlag[0] = false;
			fbxObject1->StopAnimation();
			fbxObject2->StopAnimation();
			if (fbxFlag[1] == false)
			{
				fbxFlag[1] = true;
				stopFbx->PlayAnimation(true);
				stopFbx2->PlayAnimation(true);
			}
		}
	}
}

void Player::Jump()
{
	//�W�����v
	if (((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)) && groundFlag == true) || blockStepOnFlag)
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
		dieNowTime = dieTime;
		staging.CreateFallDown(position);
		dieType = DIENOW;
	}
	if (dieType == ELECTDIE)
	{
		dieNowTime = dieTime;
		staging.CreateElect(position);
		dieType = DIENOW;

	}
	if (dieType == EATDIE)
	{
		dieNowTime = dieTime;

		dieType = DIENOW;
	}


	if (dieType == DIENOW)
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


	staging.Update();
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




