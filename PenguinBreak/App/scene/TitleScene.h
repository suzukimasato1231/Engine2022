#pragma once
#include "DirectXBase.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include"Sprite.h"
#include<memory>
#include"BaseScene.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene :public BaseScene
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

	void Init(int stageNum)override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update(int& stageNum, int m_breakBox[])override;
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
	std::unique_ptr<LightGroup>lightGroup;
private://定義
	ObjectData  m_box;							//箱OBJ
	PSR  m_boxPsr = {};							//箱PSR保存
	TextureData  m_boxGraph;					//箱画像

	SoundData  m_buttonSE = {};                 //ボタンSE

	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model> m_penginModel;		  //ペンギンモデル
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;//ペンギンFBX

	ObjectData  m_wallObj;						//壁OBJ
	PSR  m_wallPsr;								//影PSR保存

	ObjectData  m_floorObj;						//床OBJ

	//UI
	SpriteData  m_titleGraph;					//タイトル画像
	SpriteData  m_titleButtonGraph;				//ボタン画像
	int  m_buttonTime = 0;						//ボタン点滅
};


