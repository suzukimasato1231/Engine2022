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
	void Draw(Vec3 fbxPos, Vec3 angle, bool shadowFlag);
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
	const int fbxNum = 2;

	int fbxType = NULL;
	int fbxFlag = 1;
	//歩きFBX
	Model* model1 = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject1[2];
	//歩きFBX
	Model* walkModel = nullptr;
	std::unique_ptr<FBXObject3d> walkFbx[2];
	//停止FBX
	Model* stopModel = nullptr;
	std::unique_ptr<FBXObject3d> stopFbx[2];
	//感電
	Model* electModel = nullptr;
	std::unique_ptr<FBXObject3d> electFbx[2];
	//ゴール時の演出バク天
	Model* goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d> goalJumpFbx[2];
	//ゴール時の演出ハンドサイン
	Model* goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d> goalHandFbx[2];
	//ジャンプ時の演出ハンドサイン
	Model* jumpModel = nullptr;
	std::unique_ptr<FBXObject3d> jumpFbx[2];
	const int jumpTimeMax = 30;
	int jumpTime = 0;

	bool menuStopFlag = false;
};

