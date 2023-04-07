#pragma once
#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "ShadowMap.h"

extern const int window_width;
extern const int window_height;
class SceneManager :public Singleton<SceneManager>
{
private:
	friend Singleton<SceneManager>;
	/// <summary>
	/// シーンタイプ
	/// </summary>
	enum Scene
	{
		Title,
		SelectScene,
		GameScene,
		Result,
	};
	/// <summary>
	/// シーンチェンジ状況
	/// </summary>
	enum ChangeNumber
	{
		ChangeStand,
		ChangeFirst,
		ChangeEnd,
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~SceneManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
private:
	/// <summary>
	/// シーンチェンジの処理
	/// </summary>
	void SceneChange();
private://定義
	TitleScene  m_titleScene;
	StageSelect  m_stageScene;
	GameSceneManager  m_gameScene;
	ResultScene  m_resultScene;
	int  m_scene = Title;	//シーン管理
	int  m_sceneMe = Title;
	SpriteData  m_changeBlack;
	int  m_changeSceneFlag = false;
	Vec4  m_changeSceneColor = { 1.0f,1.0f,1.0f,0.0f };//シーンが変わる時の色
	bool  m_Flag = false;

	Audio* m_audio = nullptr;
	SoundData  m_bgm={};
	SoundData  m_buttonSE={};

	ShadowMap  m_shadowMapFar;
};