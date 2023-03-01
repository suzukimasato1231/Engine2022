#pragma once
#include "_DirectX.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include"Sprite.h"
#include<memory>
extern const int window_width;
extern const int window_height;
/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~TitleScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Init();
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
private:
	std::unique_ptr<LightGroup>lightGroup;
private://定義
	ObjectData box;								//箱OBJ
	PSR boxPsr = {};							//箱PSR保存
	int boxGraph;								//箱画像

	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model>penginModel;			//ペンギンモデル
	std::unique_ptr<FBXObject3d> penginHandFbx;	//ペンギンFBX

	ObjectData wallObj;							//壁OBJ
	PSR wallPsr;								//影PSR保存
		
	ObjectData floorObj;						//床OBJ

	//UI
	SpriteData titleGraph;						//タイトル画像
	SpriteData titleButtonGraph;				//ボタン画像
	int buttonTime = 0;							//ボタン点滅
};


