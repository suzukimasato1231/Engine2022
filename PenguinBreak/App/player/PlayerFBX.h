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
	FBXMAX,
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
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerFBX();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~PlayerFBX();
	/// <summary>
	/// 読み取り
	/// </summary>
	void Load();
	/// <summary>
	/// 更新
	/// </summary>
	void Update(const Vec3& fbxPos, const Vec3& angle);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="fbxPos">座標</param>
	/// <param name="angle">角度</param>
	/// <param name="shadowFlag">シャドウフラグ</param>
	void Draw(bool shadowFlag);
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
	/// <summary>
	/// メモリ削除
	/// </summary>
	void Delete();
	/// <summary>
	/// FBXを動かす
	/// </summary>
	/// <param name="fbxType">fbxタイプ</param>
	void PlayFBX(int fbxType);
	/// <summary>
	/// アニメーションを止める
	/// </summary>
	void StopAnimation();
	/// <summary>
	/// アニメーション
	/// </summary>
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

