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
	m_fbxModel = std::make_unique<Model>();
	m_fbxModel = std::unique_ptr<Model>(model1);

	Model* model2 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	m_stopModel = std::make_unique<Model>();
	m_stopModel = std::unique_ptr<Model>(model2);

	Model* model3 = FbxLoader::GetInstance()->LoadModelFromFile("penginElect", "FBX/");
	m_electModel = std::make_unique<Model>();
	m_electModel = std::unique_ptr<Model>(model3);

	Model* model4 = FbxLoader::GetInstance()->LoadModelFromFile("goalJump", "FBX/");
	m_goalJumpModel = std::make_unique<Model>();
	m_goalJumpModel = std::unique_ptr<Model>(model4);

	Model* model5 = FbxLoader::GetInstance()->LoadModelFromFile("goalHand", "FBX/");
	m_goalHandModel = std::make_unique<Model>();
	m_goalHandModel = std::unique_ptr<Model>(model5);

	Model* model6 = FbxLoader::GetInstance()->LoadModelFromFile("jumpFbx", "FBX/");
	m_jumpModel = std::make_unique<Model>();
	m_jumpModel = std::unique_ptr<Model>(model6);
 
	Model* model7 = FbxLoader::GetInstance()->LoadModelFromFile("Walking", "FBX/");
	m_walkModel = std::make_unique<Model>();
	m_walkModel = std::unique_ptr<Model>(model7);

	Model* model8 = FbxLoader::GetInstance()->LoadModelFromFile("spinFbx", "FBX/");
	m_spinModel = std::make_unique<Model>();
	m_spinModel = std::unique_ptr<Model>(model8);
  

	//3Dオブジェクトの生成とモデルのセット
	m_fbxObject1 = std::make_unique<FBXObject3d>();
	m_fbxObject1->Initialize();
	m_fbxObject1->SetModel(m_fbxModel.get());

	m_stopFbx = std::make_unique<FBXObject3d>();
	m_stopFbx->Initialize();
	m_stopFbx->SetModel(m_stopModel.get());

	m_electFbx = std::make_unique<FBXObject3d>();
	m_electFbx->Initialize();
	m_electFbx->SetModel(m_electModel.get());

	m_goalJumpFbx = std::make_unique<FBXObject3d>();
	m_goalJumpFbx->Initialize();
	m_goalJumpFbx->SetModel(m_goalJumpModel.get());

	m_goalHandFbx = std::make_unique<FBXObject3d>();
	m_goalHandFbx->Initialize();
	m_goalHandFbx->SetModel(m_goalHandModel.get());

	m_jumpFbx = std::make_unique<FBXObject3d>();
	m_jumpFbx->Initialize();
	m_jumpFbx->SetModel(m_jumpModel.get());

	m_walkFbx = std::make_unique<FBXObject3d>();
	m_walkFbx->Initialize();
	m_walkFbx->SetModel(m_walkModel.get());

	m_spinFbx = std::make_unique<FBXObject3d>();
	m_spinFbx->Initialize();
	m_spinFbx->SetModel(m_spinModel.get());
}

void PlayerFBX::Update(const Vec3& fbxPos, const Vec3& angle)
{
	m_jumpTime--;
	m_spinTime--;
	//FBX試し
	FBXObject3d* updateFbx = nullptr;
	Vec3 updatePos = fbxPos;
	updatePos.y -= 2.0f;
	Vec3 updateAngle = angle;
	switch (m_fbxType)
	{
	case FbxNone:
		updateFbx = m_stopFbx.get();
		break;
	case FbxWalk:
		updateFbx = m_fbxObject1.get();
		break;
	case FbxElectDie:
		updateFbx = m_electFbx.get();
		break;
	case FbxGoalJump:
		updateFbx = m_goalJumpFbx.get();
		break;
	case FbxGoalHand:
		updateFbx = m_goalHandFbx.get();
		break;
	case FbxJump:
		updateFbx = m_jumpFbx.get();
		break;
	case FbxWalking:
		updateFbx = m_walkFbx.get();
		break;
	case FbxSpin:
		updateFbx = m_spinFbx.get();
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
	switch (m_fbxType)
	{
	case FbxNone:
		m_stopFbx->Draw(shadowFlag);
		break;
	case FbxWalk:
		m_fbxObject1->Draw(shadowFlag);
		break;
	case FbxElectDie:
		m_electFbx->Draw(shadowFlag);
		break;
	case FbxGoalJump:
		m_goalJumpFbx->Draw(shadowFlag);
		break;
	case FbxGoalHand:
		m_goalHandFbx->Draw(shadowFlag);
		break;
	case FbxJump:
		m_jumpFbx->Draw(shadowFlag);
		break;
	case FbxWalking:
		m_walkFbx->Draw(shadowFlag);
		break;
	case FbxSpin:
		m_spinFbx->Draw(shadowFlag);
		break;
	default:
		break;
	}
}

void PlayerFBX::Reset()
{
	m_fbxType = FbxNone;
}

void PlayerFBX::PlayFBX(int fbxType)
{
	switch (fbxType)
	{
	case FbxNone:
		if (m_jumpTime > 0 || m_spinTime > 0) { break; }
		if (m_fbxFlag != FbxLoopStop)
		{
			m_fbxFlag = FbxLoopStop;
			m_stopFbx->PlayAnimation(true);
		}
		m_fbxType = fbxType;
		break;
	case FbxWalk:
		if (m_jumpTime > 0 || m_spinTime > 0) { break; }
		if (m_fbxFlag != FbxLoopRun)
		{//アニメーション開始
			m_fbxObject1->PlayAnimation(true);
			m_fbxFlag = FbxLoopRun;
		}
		m_fbxType = fbxType;
		break;
	case FbxElectDie:
		m_electFbx->PlayAnimation(false);
		m_fbxType = fbxType;
		break;
	case FbxGoalJump:
		m_goalJumpFbx->PlayAnimation(false);
		m_fbxType = fbxType;
		break;
	case FbxGoalHand:
		m_goalHandFbx->PlayAnimation(false);
		m_fbxType = fbxType;
		break;
	case FbxJump:
		m_jumpFbx->PlayAnimation(false);
		m_jumpTime = m_jumpTimeMax;
		m_fbxType = fbxType;
		break;
	case FbxWalking:
		if (m_jumpTime > 0 || m_spinTime > 0) { break; }
		if (m_fbxFlag != FbxLoopWalk)
		{
			m_walkFbx->PlayAnimation(true);
			m_fbxFlag = FbxLoopWalk;
		}
		m_fbxType = fbxType;
		break;
	case FbxSpin:
		m_spinTime = c_spinTimeMax;
		m_spinFbx->PlayAnimation(false);
		m_fbxType = fbxType;
		break;
	case FBXMAX:
		m_fbxType = fbxType;
		break;
	default:
		break;
	}
}

void PlayerFBX::StopAnimation()
{
	m_menuStopFlag = true;
	m_fbxFlag = FbxLoopMax;
	m_stopFbx->StopAnimation();
	m_fbxObject1->StopAnimation();
	m_electFbx->StopAnimation();
	m_goalJumpFbx->StopAnimation();
	m_goalHandFbx->StopAnimation();
	m_jumpFbx->StopAnimation();
	m_walkFbx->StopAnimation();
	m_spinFbx->StopAnimation();
}

void PlayerFBX::StartAnimation()
{
	if (m_menuStopFlag == false) { return; }
	m_stopFbx->PlayAnimation(true);
	m_fbxObject1->PlayAnimation(true);
	m_electFbx->PlayAnimation(false);
	m_goalJumpFbx->PlayAnimation(false);
	m_goalHandFbx->PlayAnimation(false);
	m_jumpFbx->PlayAnimation(false);
	m_walkFbx->PlayAnimation(true);
	m_spinFbx->PlayAnimation(false);
}