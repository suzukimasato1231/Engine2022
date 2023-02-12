#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "ShadowMap.h"
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

extern const int window_width;
extern const int window_height;
class SceneManagerh :public Singleton<SceneManagerh>
{
private:
	friend Singleton<SceneManagerh>;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManagerh();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~SceneManagerh();
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
	TitleScene titleScene;
	StageSelect stageScene;
	GameSceneManager gameScene;
	ResultScene resultScene;
	int scene = Title;	//シーン管理
	int sceneMe = Title;
	SpriteData changeBlack;
	int changeSceneFlag = false;
	Vec4 changeSceneColor = { 1.0f,1.0f,1.0f,0.0f };//シーンが変わる時の色
	bool Flag = false;

	Audio* audio = nullptr;
	SoundData bgm={};
	SoundData buttonSE={};

	ShadowMap shadowMapFar;
};