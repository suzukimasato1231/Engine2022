#pragma once
#include "DirectXBase.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"../App/player/Player.h"
#include"../App/stage/Stage.h"
#include"../App/ui/UI.h"
#include"../App/player/DecLifeStaging.h"
#include<memory>
#include"BaseScene.h"
extern const int window_width;
extern const int window_height;
enum class ChangeStatus
{
	ChangeClear,
	ChangeRetry,
	ChangeSelect,
};
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene:public BaseScene
{
private:
	//ゲームオーバーセレクト
	enum GameOverSelect
	{
		GameOverRetry = 1,
		GameOverSelect,
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~GameScene();
	void Init(int stageNum)override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update(int& stageNum, const int m_breakBox[])override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const int stageNum)override;
	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowDraw()override;
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw()override;
	

	void Finalize()override;
private:
	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="stageNum">ステージ</param>
	void Reset(int stageNum);
private:
	std::unique_ptr<LightGroup>lightGroup;
	std::unique_ptr<Audio> audio;
private://定義
	int  m_stageNum = 1;

	//スプライトデータ
	SpriteData  m_BGGraph;
	Vec2  m_pos = { 0.0f,0.0f };

	//ゴール時の演出はじめ
	bool  m_goalStagingFlag = false;
	int  m_goalStagingTime = 0;
	const int c_goalStagingTimeMax = 260;

	//カメラ角度
	const float c_cameraAngle = 37.5f;
	const float c_goalCamraAngleMax = 25.0f;
	float  m_goalCameraAngle = 0.0f;
	const float c_cameraSpeed = 1.0f;       //カメラの変わるスピード
	//カメラ距離
	const float c_goalDistanceMax = 100.0f;
	const float c_goalDistanceMin = 50.0f;
	float  m_goalDistance = 0.0f;
	//UIクラス
	UI  m_ui;
	//死亡時の演出クラス
	DecLifeStaging  m_decLifeStaging;

	//音データ
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
};