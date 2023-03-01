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
	vec = {};
	//音の間隔の更新
	AudioUpdate();
	//移動
	Move();
	//ジャンプ
	Jump();
	//スピン攻撃
	SpinAttack();

	staging.Update();

	position += vec;
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
	//落下死
	FallDie();
	//魚関連
	Fish();

	RedFishDie();

	Vec3 fbxPos = { oldPosition.x, oldPosition.y - 2.0f, oldPosition.z };
	pFbx.Update(fbxPos,angle);

	AnimationUpdate();
}

void Player::Draw(bool shadowFlag)
{
	staging.Draw3D();
	if (starStaging == false || moveFlag == false)
	{
		pFbx.Draw(shadowFlag);
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
	position = firstPosition;	//座標
	oldPosition = position;
	remainLives = remainLivesMax;
	fishNum = {};
	gameoverFlag = false;
	dieType = DIENULL;
	clearFlag = false;
	angle = firstAngle;	//角度
	decLifeTime = {};
	isFishDie = false;
	pFbx.Reset();
	if (moveFlag == true)
	{
		starStaging = true;
		startTime = {};
	}
	else
	{
		starStaging = false;
	}
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
	//開始時のアニメーション
	if (starStaging == false || moveFlag == false) { return; }
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

void Player::AudioUpdate()
{
	audioTime++;
	const int audioTimeMax = 201;//時間をリセットする最大値
	if (audioTime >= audioTimeMax)
	{
		audioTime = 0;
	}
}


//移動
void Player::Move()
{
	if (dieType != DIENULL || clearFlag == true || gameoverFlag == true || starStaging == true) { return; }
	//キーボード移動
	if (Input::Get()->KeybordInputArrow() == true)
	{
		if (moveFlag == true)//移動か２Dか３Dか
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
		const int audioCoolTime = 15;//音を鳴らすまでの時間
		if (groundFlag == true && audioTime % audioCoolTime == 0)
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
		const int audioCoolTime = 15;//音を鳴らすまでの時間
		if (groundFlag == true && audioTime % audioCoolTime == 0)
		{
			Audio::Get()->SoundSEPlayWave(walkSE);
		}
		float rad = Input::Get()->GetLeftAngle();
		vec.x = walkSpeed.x * sinf(-rad);
		if (moveFlag == true)
		{
			vec.z = walkSpeed.z * cosf(rad);
		}
		angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));
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
	//ジャンプ
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
	if (position.y < fallPos && dieType == DIENULL)
	{
		static const int dieTime = 30;	//死んだときの演出時間
		dieNowTime = dieTime;
		staging.CreateFallDown(position);
		Audio::Get()->SoundSEPlayWave(fallSE);
		dieType = DIENOW;
	}
	else if (dieType == ELECTDIE)
	{
		int dieTime = 200;				//死んだときの演出時間
		dieNowTime = dieTime;
		staging.CreateElect(position);
		dieType = DIENOW;
		Audio::Get()->SoundSEPlayWave(electSE);
		pFbx.PlayFBX(FbxElectDie);
	}
	else if (dieType == EATDIE)
	{
		const int dieTime = 100;		//死んだときの演出時間
		dieNowTime = dieTime;
		dieType = DIENOW;
		isFishDie = true;
	}
	else if (dieType == BOMBDIE)
	{
		const int dieTime = 50;			//死んだときの演出時間
		dieNowTime = dieTime;
		dieType = DIENOW;
		pFbx.PlayFBX(FBXMAX);
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
					position = firstPosition;	//座標
					angle = firstAngle;	//角度
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
		//100個集まったら残機１つ増える
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
	if (position.y < fallPos && dieType == DIENOW)
	{
		isFishDie = false;
	}
}