#include "PlayerFBX.h"
#include <Safe_delete.h>

PlayerFBX::PlayerFBX()
{
}

PlayerFBX::~PlayerFBX()
{
}

void PlayerFBX::Load()
{
	//モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("pengin2", "FBX/");
	stopModel = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	electModel = FbxLoader::GetInstance()->LoadModelFromFile("penginElect", "FBX/");
	goalJumpModel = FbxLoader::GetInstance()->LoadModelFromFile("goalJump", "FBX/");
	goalHandModel = FbxLoader::GetInstance()->LoadModelFromFile("goalHand", "FBX/");
	jumpModel = FbxLoader::GetInstance()->LoadModelFromFile("jumpFbx", "FBX/");
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

		goalJumpFbx[i] = std::make_unique<FBXObject3d>();
		goalJumpFbx[i]->Initialize();
		goalJumpFbx[i]->SetModel(goalJumpModel);

		goalHandFbx[i] = std::make_unique<FBXObject3d>();
		goalHandFbx[i]->Initialize();
		goalHandFbx[i]->SetModel(goalHandModel);

		jumpFbx[i] = std::make_unique<FBXObject3d>();
		jumpFbx[i]->Initialize();
		jumpFbx[i]->SetModel(jumpModel);

	}
}

void PlayerFBX::Update()
{
	jumpTime--;
}

void PlayerFBX::Draw(Vec3 fbxPos, Vec3 angle, bool shadowFlag)
{
	//FBX試し
	switch (fbxType)
	{
	case FbxNone:
		for (int i = 0; i < fbxNum; i++)
		{
			stopFbx[i]->SetPosition(fbxPos);
			stopFbx[i]->SetRotation(angle);
		}
		stopFbx[0]->Update(shadowFlag);
		stopFbx[1]->Update(false);
		break;
	case FbxWalk:
		for (int i = 0; i < fbxNum; i++)
		{
			fbxObject1[i]->SetPosition(fbxPos);
			fbxObject1[i]->SetRotation(angle);
		}
		fbxObject1[0]->Update(shadowFlag);
		fbxObject1[1]->Update(false);
		break;
	case FbxElectDie:
		for (int i = 0; i < fbxNum; i++)
		{
			electFbx[i]->SetPosition(fbxPos);
			electFbx[i]->SetRotation(angle);
		}
		electFbx[0]->Update(shadowFlag);
		electFbx[1]->Update(false);
		break;
	case FbxGoalJump:
		for (int i = 0; i < fbxNum; i++)
		{
			goalJumpFbx[i]->SetPosition(fbxPos);
			goalJumpFbx[i]->SetRotation(angle);
		}
		goalJumpFbx[0]->Update(shadowFlag);
		goalJumpFbx[1]->Update(false);
		break;
	case FbxGoalHand:
		for (int i = 0; i < fbxNum; i++)
		{
			goalHandFbx[i]->SetPosition(fbxPos);
			goalHandFbx[i]->SetRotation(angle);
		}
		goalHandFbx[0]->Update(shadowFlag);
		goalHandFbx[1]->Update(false);
		break;
	case FbxJump:
		for (int i = 0; i < fbxNum; i++)
		{
			jumpFbx[i]->SetPosition(fbxPos);
			jumpFbx[i]->SetRotation(angle);
		}
		jumpFbx[0]->Update(shadowFlag);
		jumpFbx[1]->Update(false);
		break;
	default:
		break;
	}
	switch (fbxType)
	{
	case FbxNone:
		if (shadowFlag == false) {
			stopFbx[0]->Draw();
		}
		else {
			stopFbx[1]->Draw();
		}
		break;
	case FbxWalk:
		if (shadowFlag == false) {
			fbxObject1[0]->Draw();
		}
		else {
			fbxObject1[1]->Draw();
		}
		break;
	case FbxElectDie:
		if (shadowFlag == false) {
			electFbx[0]->Draw();
		}
		else {
			electFbx[1]->Draw();
		}
		break;
	case FbxGoalJump:
		if (shadowFlag == false) {
			goalJumpFbx[0]->Draw();
		}
		else {
			goalJumpFbx[1]->Draw();
		}
		break;
	case FbxGoalHand:
		if (shadowFlag == false) {
			goalHandFbx[0]->Draw();
		}
		else {
			goalHandFbx[1]->Draw();
		}
		break;
	case FbxJump:
		if (shadowFlag == false) {
			jumpFbx[0]->Draw();
		}
		else {
			jumpFbx[1]->Draw();
		}
		break;
	default:
		break;
	}
}

void PlayerFBX::Reset()
{
	fbxType = FbxNone;
}

void PlayerFBX::Delete()
{
	safe_delete(model1);
	safe_delete(stopModel);
	safe_delete(electModel);
	safe_delete(goalJumpModel);
	safe_delete(goalHandModel);
	safe_delete(jumpModel);
}

void PlayerFBX::PlayFBX(int fbxType)
{
	switch (fbxType)
	{
	case FbxNone:
		if (jumpTime <= 0)
		{
			fbxFlag[0] = false;
			if (fbxFlag[1] == false)
			{
				fbxFlag[1] = true;
				stopFbx[0]->PlayAnimation(true);
				stopFbx[1]->PlayAnimation(true);
			}
			this->fbxType = fbxType;
		}
		break;
	case FbxWalk:
		if (jumpTime <= 0)
		{
			if (fbxFlag[0] == false)
			{//アニメーション開始
				fbxObject1[0]->PlayAnimation(true);
				fbxObject1[1]->PlayAnimation(true);
				fbxFlag[0] = true;
			}
			fbxFlag[1] = false;
			this->fbxType = fbxType;
		}
		break;
	case FbxElectDie:
		for (int i = 0; i < 2; i++)
		{
			electFbx[i]->PlayAnimation(false);
		}
		this->fbxType = fbxType;
		break;
	case FbxGoalJump:
		for (int i = 0; i < 2; i++)
		{
			goalJumpFbx[i]->PlayAnimation(false);
		}
		this->fbxType = fbxType;
		break;
	case FbxGoalHand:
		for (int i = 0; i < 2; i++)
		{
			goalHandFbx[i]->PlayAnimation(false);
		}
		this->fbxType = fbxType;
		break;
	case FbxJump:
		for (int i = 0; i < 2; i++)
		{
			jumpFbx[i]->PlayAnimation(false);
		}
		jumpTime = jumpTimeMax;
		this->fbxType = fbxType;
		break;
	default:
		break;
	}
}

void PlayerFBX::StopAnimation()
{
	menuStopFlag = true;
	for (size_t i = 0; i < fbxNum; i++)
	{
		stopFbx[i]->StopAnimation();
		fbxObject1[i]->StopAnimation();
		fbxFlag[i] = false;
		electFbx[i]->StopAnimation();
		goalJumpFbx[i]->StopAnimation();
		goalHandFbx[i]->StopAnimation();
		jumpFbx[i]->StopAnimation();
	}
}

void PlayerFBX::StartAnimation()
{
	if (menuStopFlag == true)
	{
		for (size_t i = 0; i < fbxNum; i++)
		{
			stopFbx[i]->PlayAnimation(true);
			fbxObject1[i]->PlayAnimation(true);
			electFbx[i]->PlayAnimation(false);
			goalJumpFbx[i]->PlayAnimation(false);
			goalHandFbx[i]->PlayAnimation(false);
			jumpFbx[i]->PlayAnimation(false);
		}
	}
}
