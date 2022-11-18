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

	//モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("pengin2");
	stopModel = FbxLoader::GetInstance()->LoadModelFromFile("movePengin");
	electModel = FbxLoader::GetInstance()->LoadModelFromFile("penginElect");

	for (int i = 0; i < 2; i++)
	{
		//3Dオブジェクトの生成とモデルのセット
		fbxObject1[i] = std::make_unique<FBXObject3d>();
		fbxObject1[i]->Initialize();
		fbxObject1[i]->SetModel(model1);

		//3Dオブジェクトの生成とモデルのセット
		stopFbx[i] = std::make_unique<FBXObject3d>();
		stopFbx[i]->Initialize();
		stopFbx[i]->SetModel(stopModel);

		//3Dオブジェクトの生成とモデルのセット
		electFbx[i] = std::make_unique<FBXObject3d>();
		electFbx[i]->Initialize();
		electFbx[i]->SetModel(electModel);
	}
}

void Player::Update()
{
	oldPosition = position;
	oldGroundFlag = groundFlag;
	vec = {};
	//移動
	Move();
	//ジャンプ
	Jump();

	position += vec;
	pSphere.center = XMVectorSet(position.x, position.y, position.z, 1);
	pBox.maxPosition = XMVectorSet(position.x + pScale.x / 2, position.y + pScale.y / 2, position.z + pScale.z / 2, 1);
	pBox.minPosition = XMVectorSet(position.x - pScale.x / 2, position.y - pScale.y / 2, position.z - pScale.z / 2, 1);
	//落下死
	FallDie();
	//魚関連
	Fish();

	RedFishDie();
}

void Player::Draw(bool shadowFlag)
{
	staging.Draw3D();

	FbxDraw(shadowFlag);

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
	position = { 70.0f,25.0f,80.0f };	//座標
	oldPosition = position;
	remainLives = remainLivesMax;
	fishNum = 0;
	gameoverFlag = false;
	dieType = DIENULL;
}

void Player::Delete()
{
	safe_delete(model1);
	safe_delete(stopModel);
	safe_delete(electModel);
}

void Player::FbxDraw(bool shadowFlag)
{
	Vec3 fbxPos = { position.x, position.y - 2.0f, position.z };
	//FBX試し
	switch (fbxType)
	{
	case None:
		stopFbx[0]->SetPosition(fbxPos);
		stopFbx[0]->SetRotation(angle);
		stopFbx[1]->SetPosition(fbxPos);
		stopFbx[1]->SetRotation(angle);


		stopFbx[0]->Update(shadowFlag);
		stopFbx[1]->Update(false);
		break;
	case Walk:
		fbxObject1[0]->SetPosition(fbxPos);
		fbxObject1[0]->SetRotation(angle);
		fbxObject1[1]->SetPosition(fbxPos);
		fbxObject1[1]->SetRotation(angle);

		fbxObject1[0]->Update(shadowFlag);
		fbxObject1[1]->Update(false);
		break;
	case ElectDie:
		electFbx[0]->SetPosition(fbxPos);
		electFbx[0]->SetRotation(angle);
		electFbx[1]->SetPosition(fbxPos);
		electFbx[1]->SetRotation(angle);

		electFbx[0]->Update(shadowFlag);
		electFbx[1]->Update(false);
		break;
	default:
		break;
	}
	switch (fbxType)
	{
	case None:
		if (shadowFlag == false)
		{
			stopFbx[0]->Draw();
		}
		else
		{
			stopFbx[1]->Draw();
		}
		break;
	case Walk:
		if (shadowFlag == false)
		{
			fbxObject1[0]->Draw();
		}
		else
		{
			fbxObject1[1]->Draw();
		}
		break;
	case ElectDie:
		if (shadowFlag == false)
		{
			electFbx[0]->Draw();
		}
		else
		{
			electFbx[1]->Draw();
		}
		break;
	default:
		break;
	}
	Object::Get()->PreDraw(shadowFlag);
}

//移動
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
		//移動
		if (Input::Get()->KeybordPush(DIK_RIGHT))
		{
			vec.x += speed.x;
		}
		if (Input::Get()->KeybordPush(DIK_LEFT))
		{
			vec.x -= speed.x;
		}
		//コントローラー移動
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
			{//アニメーション開始
				stopFbx[0]->StopAnimation();
				stopFbx[1]->StopAnimation();
				fbxObject1[0]->PlayAnimation(true);
				fbxObject1[1]->PlayAnimation(true);
				fbxFlag[0] = true;
			}
			fbxFlag[1] = false;
			fbxType = Walk;
		}
		else
		{
			fbxType = None;
			fbxFlag[0] = false;
			fbxObject1[0]->StopAnimation();
			fbxObject1[1]->StopAnimation();
			if (fbxFlag[1] == false)
			{
				fbxFlag[1] = true;
				stopFbx[0]->PlayAnimation(true);
				stopFbx[1]->PlayAnimation(true);
			}
		}
	}
}

void Player::Jump()
{
	//ジャンプ
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
		dieType = DIENOW;
	}
	if (dieType == ELECTDIE)
	{
		static const int dieTime = 200;	//死んだときの演出時間
		dieNowTime = dieTime;
		staging.CreateElect(position);
		dieType = DIENOW;
		fbxType = ElectDie;
		for (int i = 0; i < 2; i++)
		{
			electFbx[i]->PlayAnimation(false);
		}
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
		}
		else if (remainLives > 0)
		{
			position = { 70.0f,20.0f,80.0f };	//座標
			oldPosition = position;
			remainLives--;
			dieType = DIENULL;
			isFishDie = false;
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




