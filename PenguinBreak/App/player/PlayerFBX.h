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
	int m_fbxType = NULL;
	int  m_fbxFlag = 1;
	//歩きFBX
	std::unique_ptr<Model>  m_fbxModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_fbxObject1;
	//歩きFBX
	std::unique_ptr<Model>  m_walkModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_walkFbx;
	//停止FBX
	std::unique_ptr<Model> m_stopModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_stopFbx;
	//スピンFBX
	std::unique_ptr<Model>  m_spinModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_spinFbx;
	const int c_spinTimeMax = 30;
	int  m_spinTime = 0;
	//感電
	std::unique_ptr<Model>  m_electModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_electFbx;
	//ゴール時の演出バク天
	std::unique_ptr<Model>  m_goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_goalJumpFbx;
	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model>  m_goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_goalHandFbx;
	//ジャンプ時の演出ハンドサイン
	std::unique_ptr<Model>  m_jumpModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_jumpFbx;
	const int  m_jumpTimeMax = 30;
	int  m_jumpTime = 0;

	bool  m_menuStopFlag = false;
};

