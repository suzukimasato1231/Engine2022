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
	walkModel = FbxLoader::GetInstance()->LoadModelFromFile("Walking", "FBX/");
	spinModel = FbxLoader::GetInstance()->LoadModelFromFile("spinFbx", "FBX/");

	//3Dオブジェクトの生成とモデルのセット
	fbxObject1 = std::make_unique<FBXObject3d>();
	fbxObject1->Initialize();
	fbxObject1->SetModel(model1);

	stopFbx = std::make_unique<FBXObject3d>();
	stopFbx->Initialize();
	stopFbx->SetModel(stopModel);

	electFbx = std::make_unique<FBXObject3d>();
	electFbx->Initialize();
	electFbx->SetModel(electModel);

	goalJumpFbx = std::make_unique<FBXObject3d>();
	goalJumpFbx->Initialize();
	goalJumpFbx->SetModel(goalJumpModel);

	goalHandFbx = std::make_unique<FBXObject3d>();
	goalHandFbx->Initialize();
	goalHandFbx->SetModel(goalHandModel);

	jumpFbx = std::make_unique<FBXObject3d>();
	jumpFbx->Initialize();
	jumpFbx->SetModel(jumpModel);

	walkFbx = std::make_unique<FBXObject3d>();
	walkFbx->Initialize();
	walkFbx->SetModel(walkModel);

	spinFbx = std::make_unique<FBXObject3d>();
	spinFbx->Initialize();
	spinFbx->SetModel(spinModel);
}

void PlayerFBX::Update()
{
	jumpTime--;
	spinTime--;
}

void PlayerFBX::Draw(const Vec3& fbxPos, const Vec3& angle, bool shadowFlag)
{
	//FBX試し
	if (shadowFlag == false)
	{
		switch (fbxType)
		{
		case FbxNone:
			stopFbx->SetPosition(fbxPos);
			stopFbx->SetRotation(angle);
			stopFbx->Update();
			break;
		case FbxWalk:
			fbxObject1->SetPosition(fbxPos);
			fbxObject1->SetRotation(angle);
			fbxObject1->Update();
			break;
		case FbxElectDie:
			electFbx->SetPosition(fbxPos);
			electFbx->SetRotation(angle);
			electFbx->Update();
			break;
		case FbxGoalJump:
			goalJumpFbx->SetPosition(fbxPos);
			goalJumpFbx->SetRotation(angle);
			goalJumpFbx->Update();
			break;
		case FbxGoalHand:
			goalHandFbx->SetPosition(fbxPos);
			goalHandFbx->SetRotation(angle);
			goalHandFbx->Update();
			break;
		case FbxJump:
			jumpFbx->SetPosition(fbxPos);
			jumpFbx->SetRotation(angle);
			jumpFbx->Update();
			break;
		case FbxWalking:
			walkFbx->SetPosition(fbxPos);
			walkFbx->SetRotation(angle);
			walkFbx->Update();
			break;
		case FbxSpin:
			spinFbx->SetPosition(fbxPos);
			spinFbx->SetRotation(Vec3(angle.x + 30.0f, angle.y, angle.z));
			spinFbx->Update();
			break;
		default:
			break;
		}
	}
	switch (fbxType)
	{
	case FbxNone:
		stopFbx->Draw(shadowFlag);
		break;
	case FbxWalk:
		fbxObject1->Draw(shadowFlag);
		break;
	case FbxElectDie:
		electFbx->Draw(shadowFlag);
		break;
	case FbxGoalJump:
		goalJumpFbx->Draw(shadowFlag);
		break;
	case FbxGoalHand:
		goalHandFbx->Draw(shadowFlag);
		break;
	case FbxJump:
		jumpFbx->Draw(shadowFlag);
		break;
	case FbxWalking:
		walkFbx->Draw(shadowFlag);
		break;
	case FbxSpin:
		spinFbx->Draw(shadowFlag);
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
	safe_delete(walkModel);
	safe_delete(spinModel);
}

void PlayerFBX::PlayFBX(int fbxType)
{
	switch (fbxType)
	{
	case FbxNone:
		if (jumpTime <= 0 && spinTime <= 0)
		{
			if (fbxFlag != FbxLoopStop)
			{
				fbxFlag = FbxLoopStop;
				stopFbx->PlayAnimation(true);
			}
			this->fbxType = fbxType;
		}
		break;
	case FbxWalk:
		if (jumpTime <= 0 && spinTime <= 0)
		{
			if (fbxFlag != FbxLoopRun)
			{//アニメーション開始
				fbxObject1->PlayAnimation(true);
				fbxFlag = FbxLoopRun;
			}
			this->fbxType = fbxType;
		}
		break;
	case FbxElectDie:
		electFbx->PlayAnimation(false);
		this->fbxType = fbxType;
		break;
	case FbxGoalJump:
		goalJumpFbx->PlayAnimation(false);
		this->fbxType = fbxType;
		break;
	case FbxGoalHand:
		goalHandFbx->PlayAnimation(false);
		this->fbxType = fbxType;
		break;
	case FbxJump:
		jumpFbx->PlayAnimation(false);
		jumpTime = jumpTimeMax;
		this->fbxType = fbxType;
		break;
	case FbxWalking:
		if (jumpTime <= 0 && spinTime <= 0)
		{
			if (fbxFlag != FbxLoopWalk)
			{
				walkFbx->PlayAnimation(true);
				fbxFlag = FbxLoopWalk;
			}
			this->fbxType = fbxType;
		}
		break;
	case FbxSpin:
		spinTime = spinTimeMax;
		spinFbx->PlayAnimation(false);
		this->fbxType = fbxType;
		break;
	default:
		break;
	}
}

void PlayerFBX::StopAnimation()
{
	menuStopFlag = true;
	fbxFlag = FbxLoopMax;
	stopFbx->StopAnimation();
	fbxObject1->StopAnimation();
	electFbx->StopAnimation();
	goalJumpFbx->StopAnimation();
	goalHandFbx->StopAnimation();
	jumpFbx->StopAnimation();
	walkFbx->StopAnimation();
	spinFbx->StopAnimation();
}

void PlayerFBX::StartAnimation()
{
	if (menuStopFlag == false) { return; }

	stopFbx->PlayAnimation(true);
	fbxObject1->PlayAnimation(true);
	electFbx->PlayAnimation(false);
	goalJumpFbx->PlayAnimation(false);
	goalHandFbx->PlayAnimation(false);
	jumpFbx->PlayAnimation(false);
	walkFbx->PlayAnimation(true);
	spinFbx->PlayAnimation(false);

}
