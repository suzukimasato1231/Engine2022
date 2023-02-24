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
	oldPosition = position;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);

	staging.Init();

	walkSE = Audio::SoundLoadWave("Resources/sound/SE/walk.wav");
	fallSE = Audio::SoundLoadWave("Resources/sound/SE/fall.wav");
	electSE = Audio::SoundLoadWave("Resources/sound/SE/elect.wav");
	pFbx.Load();
}

void Player::Update()
{
	if (gameoverFlag == true) { return; }
	oldPosition = position;
	oldGroundFlag = groundFlag;
	audioTime++;
	if (audioTime >= 201)
	{
		audioTime = 0;
	}
	vec = {};
	//�ړ�
	Move();
	//�W�����v
	Jump();
	//�X�s���U��
	SpinAttack();

	staging.Update();

	position += vec;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
	//������
	FallDie();
	//���֘A
	Fish();

	RedFishDie();

	pFbx.Update();

	AnimationUpdate();

}

void Player::Draw(bool shadowFlag)
{
	staging.Draw3D();
	if (starStaging == false || moveFlag == false)
	{
		FbxDraw(shadowFlag);
	}
}

void Player::DrawParticle()
{
	staging.Draw();
}

void Player::SetPosition(const Vec3& position)
{
	this->position = position;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
}


void Player::Reset()
{
	position = { 90.0f,25.0f,80.0f };	//���W
	oldPosition = position;
	remainLives = remainLivesMax;
	fishNum = 0;
	gameoverFlag = false;
	dieType = DIENULL;
	clearFlag = false;
	angle = { -30.0f,180.0f,0.0f };	//�p�x
	decLifeTime = 0;
	isFishDie = false;
	pFbx.Reset();
	if (moveFlag == true)
	{
		starStaging = true;
		startTime = 0;
	}
	else
	{
		starStaging = false;
	}
}

void Player::Delete()
{
	pFbx.Delete();
}

void Player::GoalStaging(int fbxType)
{
	angle.y = 180.0f;
	pFbx.PlayFBX(fbxType);
}

void Player::StopAnimation()
{
	pFbx.StopAnimation();
}

void Player::SpinAttack()
{
	spinFlag = false;
	if (((Input::Get()->KeybordPush(DIK_F) || Input::Get()->ControllerDown(ButtonX))
		&& starStaging == false && dieType == DIENULL && clearFlag == false && spinCoolTime <= 0))
	{
		pFbx.PlayFBX(FbxSpin);
		spinCoolTime = spinCoolTimeMax;
		spinAttack.maxPosition = XMVectorSet(oldPosition.x + spinScale, oldPosition.y + 1, oldPosition.z + spinScale, 1);
		spinAttack.minPosition = XMVectorSet(oldPosition.x - spinScale, oldPosition.y - 0, oldPosition.z - spinScale, 1);
		spinFlag = true;
	}

	if (spinCoolTime >= spinCoolTimeMax - 10)
	{
		spinAttack.maxPosition = XMVectorSet(oldPosition.x + spinScale, oldPosition.y + 1, oldPosition.z + spinScale, 1);
		spinAttack.minPosition = XMVectorSet(oldPosition.x - spinScale, oldPosition.y - 0, oldPosition.z - spinScale, 1);
		spinFlag = true;
	}

	if (spinCoolTime >= 0)
	{
		spinCoolTime--;
	}

}

void Player::AnimationUpdate()
{
	//�J�n���̃A�j���[�V����
	if (starStaging == true && moveFlag == true)
	{
		if (startTime >= startTimeMax - 40)
		{
			staging.CreateStart(position);
		}
		startTime++;
		if (startTime >= startTimeMax)
		{
			starStaging = false;
			startTime = 0;
		}
	}
}

void Player::FbxDraw(bool shadowFlag)
{
	Vec3 fbxPos = { position.x, position.y - 2.0f, position.z };

	pFbx.Draw(fbxPos, angle, shadowFlag);
}

//�ړ�
void Player::Move()
{
	if (dieType != DIENULL || clearFlag == true || gameoverFlag == true || starStaging == true) { return; }
	//�L�[�{�[�h�ړ�
	if (Input::Get()->KeybordInputArrow() == true)
	{
		if (moveFlag == true)//�ړ����QD���RD��
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
	}
	//�R���g���[���[�ړ�
	if (Input::Get()->ConLeftInput())
	{
		if (groundFlag == true && audioTime % 15 == 0)
		{
			Audio::Get()->SoundSEPlayWave(walkSE);
		}
		float rad = Input::Get()->GetLeftAngle();
		vec.x = speed.x * sinf(-rad);
		if (moveFlag == true)
		{
			vec.z = speed.z * cosf(rad);;
		}
		angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));
		if (walkTime < 0)
		{
			staging.CreateWalk(position, vec);
			walkTime = walkTimeMax;
		}
		walkTime--;

		pFbx.PlayFBX(FbxWalk);
	}
	else if (Input::Get()->ConLeftInputS())
	{
		if (groundFlag == true && audioTime % 20 == 0)
		{
			Audio::Get()->SoundSEPlayWave(walkSE);
		}
		float rad = Input::Get()->GetLeftAngle();
		const Vec3 speeds = { 1.0f,1.0f,1.0f };
		vec.x = speeds.x * sinf(-rad);
		if (moveFlag == true)
		{
			vec.z = speeds.z * cosf(rad);
		}
		angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));// -59.8f);
		if (walkTime < 0)
		{
			staging.CreateWalk(position, vec);
			walkTime = walkTimeMax;
		}
		walkTime--;

		pFbx.PlayFBX(FbxWalking);
	}
	else
	{
		pFbx.PlayFBX(FbxNone);
	}
}

void Player::Jump()
{
	//�W�����v
	if (((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		&& groundFlag == true && starStaging == false && dieType == DIENULL && clearFlag == false) || blockStepOnFlag)
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

		pFbx.PlayFBX(FbxJump);
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
	if (position.y < -30.0f && dieType == DIENULL)
	{
		static const int dieTime = 30;	//���񂾂Ƃ��̉��o����
		dieNowTime = dieTime;
		staging.CreateFallDown(position);
		Audio::Get()->SoundSEPlayWave(fallSE);
		dieType = DIENOW;
	}
	else if (dieType == ELECTDIE)
	{
		int dieTime = 200;	//���񂾂Ƃ��̉��o����
		dieNowTime = dieTime;
		staging.CreateElect(position);
		dieType = DIENOW;
		Audio::Get()->SoundSEPlayWave(electSE);
		pFbx.PlayFBX(FbxElectDie);
	}
	else if (dieType == EATDIE)
	{
		const int dieTime = 100;	//���񂾂Ƃ��̉��o����
		dieNowTime = dieTime;
		dieType = DIENOW;
		isFishDie = true;
	}
	else if (dieType == BOMBDIE)
	{
		const int dieTime = 50;	//���񂾂Ƃ��̉��o����
		dieNowTime = dieTime;
		dieType = DIENOW;
		pFbx.PlayFBX(FBXMAX);
	}


	if (dieType == DIENOW)
	{
		if (dieNowTime > 0)
		{
			dieNowTime--;
			//�Ó]�J�n
			if (dieNowTime == 1)
			{
				decLifeTime = 50;
			}
		}
		else
		{
			if (remainLives > 0)
			{
				decLifeTime--;
				if (decLifeTime <= 0)
				{
					position = { 90.0f,30.0f,80.0f };	//���W
					angle = { -30.0f,180.0f,0.0f };	//�p�x
					oldPosition = position;
					remainLives--;
					isFishDie = false;
					dieType = DIENULL;
					starStaging = true;
				}
			}
			else if (remainLives == 0)
			{
				gameoverFlag = true;
				dieType = DIENULL;
			}
		}
	}
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

		//100�W�܂�����c�@�P������
		if (fishNum >= 100)
		{
			fishNum -= 100;
			remainLives++;
		}
	}
}

void Player::RedFishDie()
{
	if (isFishDie == false) { return; }

	position = fishDiePos;
	oldPosition = position;

	angle.x = fishDieAngle.x;
	if (position.y < -30.0f && dieType == DIENOW)
	{
		isFishDie = false;
	}

}