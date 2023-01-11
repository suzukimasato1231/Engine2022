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
	pSphere.radius = 7.0f;
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
	if (gameoverFlag == false)
	{
		oldPosition = position;
		oldGroundFlag = groundFlag;
		audioTime++;
		if (audioTime >= 201)
		{
			audioTime = 0;
		}
		vec = {};
		//移動
		Move();
		//ジャンプ
		Jump();

		staging.Update();

		position += vec;
		pSphere.center = XMVectorSet(position.x, position.y, position.z, 1);
		pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
		pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
		//落下死
		FallDie();
		//魚関連
		Fish();

		RedFishDie();

		pFbx.Update();
		//開始時のアニメーション
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
	position = { 90.0f,25.0f,80.0f };	//座標
	oldPosition = position;
	remainLives = remainLivesMax;
	fishNum = 0;
	gameoverFlag = false;
	dieType = DIENULL;
	clearFlag = false;
	angle = { -30.0f,180.0f,0.0f };	//角度
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

void Player::FbxDraw(bool shadowFlag)
{
	Vec3 fbxPos = { position.x, position.y - 2.0f, position.z };

	pFbx.Draw(fbxPos, angle, shadowFlag);
}

//移動
void Player::Move()
{
	if (dieType == DIENULL && clearFlag == false && gameoverFlag == false && starStaging == false)
	{
		if (Input::Get()->KeybordInputArrow() == true)
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
			//移動
			if (Input::Get()->KeybordPush(DIK_RIGHT))
			{
				vec.x += speed.x;
			}
			if (Input::Get()->KeybordPush(DIK_LEFT))
			{
				vec.x -= speed.x;
			}
		}
		//コントローラー移動
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
				vec.z = speed.z * cosf(rad);
			}
			angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));// -59.8f);
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
			Vec3 speeds = { 1.0f,1.0f,1.0f };
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
}

void Player::Jump()
{
	//ジャンプ
	if (((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)) && groundFlag == true && clearFlag == false) || blockStepOnFlag)
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

	//重力加算
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
		static const int dieTime = 30;	//死んだときの演出時間
		dieNowTime = dieTime;
		staging.CreateFallDown(position);
		Audio::Get()->SoundSEPlayWave(fallSE);
		dieType = DIENOW;
	}
	if (dieType == ELECTDIE)
	{
		static const int dieTime = 200;	//死んだときの演出時間
		dieNowTime = dieTime;
		staging.CreateElect(position);
		dieType = DIENOW;
		Audio::Get()->SoundSEPlayWave(electSE);
		pFbx.PlayFBX(FbxElectDie);
	}
	if (dieType == EATDIE)
	{
		static const int dieTime = 100;	//死んだときの演出時間
		dieNowTime = dieTime;
		dieType = DIENOW;
		isFishDie = true;
	}


	if (dieType == DIENOW)
	{
		if (dieNowTime > 0)
		{
			dieNowTime--;
			//暗転開始
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
					position = { 90.0f,30.0f,80.0f };	//座標
					angle = { -30.0f,180.0f,0.0f };	//角度
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
	}

	//100個集まったら残機１つ増える
	if (fishNum >= 100)
	{
		fishNum -= 100;
		remainLives++;
	}
}

void Player::RedFishDie()
{
	if (isFishDie == true && dieType == DIENOW)
	{
		position = fishDiePos;
		oldPosition = position;

		angle.x = fishDieAngle.x;
		if (position.y < -30.0f && dieType == DIENOW)
		{
			isFishDie = false;
		}
	}
}