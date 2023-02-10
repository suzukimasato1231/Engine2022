#pragma once
#include"FBXObject3d.h"
#include<memory>
/// <summary>
/// プレイヤーFBXの状態
/// </summary>
enum PlayerFBXType
{
	FbxNone,
	FbxWalk,
	FbxElectDie,
	FbxGoalJump,
	FbxGoalHand,
	FbxJump,
	FbxWalking,
	FbxSpin,
};
/// <summary>
/// プレイヤーのFBXクラス
/// </summary>
class PlayerFBX
{
private:
	enum LoopFbx
	{
		FbxLoopStop,
		FbxLoopWalk,
		FbxLoopRun,
		FbxLoopMax,
	};

public:
	PlayerFBX();

	~PlayerFBX();
	//FBX読み取り
	void Load();

	void Update();
	//描画
	void Draw(const Vec3& fbxPos, const Vec3& angle, bool shadowFlag);
	//リセット
	void Reset();
	//メモリ削除
	void Delete();
	//FBXを動かす
	void PlayFBX(int fbxType);
	//アニメーションを止める
	void StopAnimation();
	//アニメーションスタート
	void StartAnimation();
private:
	int fbxType = NULL;
	int fbxFlag = 1;
	//歩きFBX
	Model* model1 = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject1;
	//歩きFBX
	Model* walkModel = nullptr;
	std::unique_ptr<FBXObject3d> walkFbx;
	//停止FBX
	Model* stopModel = nullptr;
	std::unique_ptr<FBXObject3d> stopFbx;
	//スピンFBX
	Model* spinModel = nullptr;
	std::unique_ptr<FBXObject3d> spinFbx;
	const int spinTimeMax = 30;
	int spinTime = 0;
	//感電
	Model* electModel = nullptr;
	std::unique_ptr<FBXObject3d> electFbx;
	//ゴール時の演出バク天
	Model* goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d> goalJumpFbx;
	//ゴール時の演出ハンドサイン
	Model* goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d> goalHandFbx;
	//ジャンプ時の演出ハンドサイン
	Model* jumpModel = nullptr;
	std::unique_ptr<FBXObject3d> jumpFbx;
	const int jumpTimeMax = 30;
	int jumpTime = 0;

	bool menuStopFlag = false;
};

