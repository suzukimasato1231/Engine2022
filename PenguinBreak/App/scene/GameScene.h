#pragma once
#include "_DirectX.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"../App/player/Player.h"
#include"../App/stage/Stage.h"
#include"../App/ui/UI.h"
#include"../App/player/DecLifeStaging.h"
#include<memory>
extern const int window_width;
extern const int window_height;
enum ChangeStatus
{
	ChangeClear,
	ChangeRetry,
	ChangeSelect,
};
/// <summary>
/// ゲームシーン
/// </summary>
class GameSceneManager
{
private:
	//ゲームオーバーセレクト
	enum GameOverSelect
	{
		GameOverSelect = 1,
		GameOverRetry,
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSceneManager();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~GameSceneManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Init(int stageNum);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowDraw();
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw();
	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="stageNum">ステージ</param>
	void Reset(int stageNum);
public:
	bool GetChangeScene() { return  m_changeScene; }

	int GetChangeNum() { return  m_changeNum; }
private:
	std::unique_ptr<LightGroup>lightGroup;
	std::unique_ptr<Audio> audio;
private://定義
	int  m_stageNum = 1;

	//スプライトデータ
	SpriteData  m_BGGraph;

	Vec2  m_pos = { 0.0f,0.0f };

	//シーンが変わるかどうか
	bool  m_changeScene = false;
	//ゲームオーバー時
	int  m_changeNum = 0;

	//ゴール時の演出はじめ
	bool  m_goalStagingFlag = false;
	int  m_goalStagingTime = 0;
	const int c_goalStagingTimeMax = 260;

	//カメラ角度
	const float c_cameraAngle = 37.5f;
	const float c_goalCamraAngleMax = 25.0f;
	float  m_goalCameraAngle = 0.0f;
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