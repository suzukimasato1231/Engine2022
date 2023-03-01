#include "PlayerFBX.h"
#include <Safe_delete.h>

PlayerFBX::PlayerFBX()
{}

PlayerFBX::~PlayerFBX()
{}

void PlayerFBX::Load()
{
	//モデル名を指定してファイル読み込み
	Model* model1 = FbxLoader::GetInstance()->LoadModelFromFile("pengin2", "FBX/");
	fbxModel = std::make_unique<Model>();
	fbxModel = std::unique_ptr<Model>(model1);

	Model* model2 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	stopModel = std::make_unique<Model>();
	stopModel = std::unique_ptr<Model>(model2);

	Model* model3 = FbxLoader::GetInstance()->LoadModelFromFile("penginElect", "FBX/");
	electModel = std::make_unique<Model>();
	electModel = std::unique_ptr<Model>(model3);

	Model* model4 = FbxLoader::GetInstance()->LoadModelFromFile("goalJump", "FBX/");
	goalJumpModel = std::make_unique<Model>();
	goalJumpModel = std::unique_ptr<Model>(model4);

	Model* model5 = FbxLoader::GetInstance()->LoadModelFromFile("goalHand", "FBX/");
	goalHandModel = std::make_unique<Model>();
	goalHandModel = std::unique_ptr<Model>(model5);

	Model* model6 = FbxLoader::GetInstance()->LoadModelFromFile("jumpFbx", "FBX/");
	jumpModel = std::make_unique<Model>();
	jumpModel = std::unique_ptr<Model>(model6);
 
	Model* model7 = FbxLoader::GetInstance()->LoadModelFromFile("Walking", "FBX/");
	walkModel = std::make_unique<Model>();
	walkModel = std::unique_ptr<Model>(model7);

	Model* model8 = FbxLoader::GetInstance()->LoadModelFromFile("spinFbx", "FBX/");
	spinModel = std::make_unique<Model>();
	spinModel = std::unique_ptr<Model>(model8);
  

	//3Dオブジェクトの生成とモデルのセット
	fbxObject1 = std::make_unique<FBXObject3d>();
	fbxObject1->Initialize();
	fbxObject1->SetModel(fbxModel.get());

	stopFbx = std::make_unique<FBXObject3d>();
	stopFbx->Initialize();
	stopFbx->SetModel(stopModel.get());

	electFbx = std::make_unique<FBXObject3d>();
	electFbx->Initialize();
	electFbx->SetModel(electModel.get());

	goalJumpFbx = std::make_unique<FBXObject3d>();
	goalJumpFbx->Initialize();
	goalJumpFbx->SetModel(goalJumpModel.get());

	goalHandFbx = std::make_unique<FBXObject3d>();
	goalHandFbx->Initialize();
	goalHandFbx->SetModel(goalHandModel.get());

	jumpFbx = std::make_unique<FBXObject3d>();
	jumpFbx->Initialize();
	jumpFbx->SetModel(jumpModel.get());

	walkFbx = std::make_unique<FBXObject3d>();
	walkFbx->Initialize();
	walkFbx->SetModel(walkModel.get());

	spinFbx = std::make_unique<FBXObject3d>();
	spinFbx->Initialize();
	spinFbx->SetModel(spinModel.get());
}

void PlayerFBX::Update(const Vec3& fbxPos, const Vec3& angle)
{
	jumpTime--;
	spinTime--;

	//FBX試し
	FBXObject3d* updateFbx = nullptr;
	Vec3 updatePos = fbxPos;
	Vec3 updateAngle = angle;
	switch (fbxType)
	{
	case FbxNone:
		updateFbx = stopFbx.get();
		break;
	case FbxWalk:
		updateFbx = fbxObject1.get();
		break;
	case FbxElectDie:
		updateFbx = electFbx.get();
		break;
	case FbxGoalJump:
		updateFbx = goalJumpFbx.get();
		break;
	case FbxGoalHand:
		updateFbx = goalHandFbx.get();
		break;
	case FbxJump:
		updateFbx = jumpFbx.get();
		break;
	case FbxWalking:
		updateFbx = walkFbx.get();
		break;
	case FbxSpin:
		updateFbx = spinFbx.get();
		updateAngle = Vec3(angle.x + 30.0f, angle.y, angle.z);
		break;
	default:
		break;
	}
	if (updateFbx != nullptr)
	{
		updateFbx->SetPosition(updatePos);
		updateFbx->SetRotation(updateAngle);
		updateFbx->Update();
	}

}

void PlayerFBX::Draw(bool shadowFlag)
{
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



void PlayerFBX::PlayFBX(int fbxType)
{
	switch (fbxType)
	{
	case FbxNone:
		if (jumpTime > 0 || spinTime > 0) { break; }
		if (fbxFlag != FbxLoopStop)
		{
			fbxFlag = FbxLoopStop;
			stopFbx->PlayAnimation(true);
		}
		this->fbxType = fbxType;
		break;
	case FbxWalk:
		if (jumpTime > 0 || spinTime > 0) { break; }
		if (fbxFlag != FbxLoopRun)
		{//アニメーション開始
			fbxObject1->PlayAnimation(true);
			fbxFlag = FbxLoopRun;
		}
		this->fbxType = fbxType;
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
		if (jumpTime > 0 || spinTime > 0) { break; }
		if (fbxFlag != FbxLoopWalk)
		{
			walkFbx->PlayAnimation(true);
			fbxFlag = FbxLoopWalk;
		}
		this->fbxType = fbxType;
		break;
	case FbxSpin:
		spinTime = spinTimeMax;
		spinFbx->PlayAnimation(false);
		this->fbxType = fbxType;
		break;
	case FBXMAX:
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