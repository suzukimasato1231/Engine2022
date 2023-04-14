#include <Object.h>
#include<memory>
#include"FBXObject3d.h"
#include<Audio.h>
#include"BaseScene.h"
#include<Sprite.h>
/// <summary>
/// シーン移動
/// </summary>
enum class ResultNext
{
	ResultNextStage,
	ResultSelect,
};

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene:public BaseScene
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ResultScene();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~ResultScene();
	/// <summary>
	/// ループ初期化
	/// </summary>
	void Init(int stageNum)override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update(int& stageNum, int m_breakBox[])override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageNum">ステージ</param>
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
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData  m_resultOBJ;
	const int c_resultTimeMax = 500;//リザルトが出るまでの最大時間
	int  m_resultTime = 0;          //リザルトが出るまでの時間
	const int c_buttonMax = 60;     //点滅の間隔
	const int c_clearTimeMax = 30;  //クリア画面を出す時間
	const int c_numberTime = 60;    //クリアしてから数字を出す時間
	const int stageMax = 3;         //最大ステージ数
	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model>  m_penginModel;
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;
	const Vec3 fbxScale = { 0.015f,0.015f,0.015f };//fbxの大きさ

	PSR  m_objectPsr = {};
	ObjectData  m_fishObj;
	ObjectData  m_floorObj;

	//壊れた箱リザルト
	SpriteData  m_uiNumber[10]={};
	SpriteData  m_uiSlash={};
	SpriteData  m_boxGraph={};

	SpriteData  m_clearGraph;
	SpriteData  m_selectGraph;
	SpriteData  m_nextGraph;
	//int  m_nextScene = 0;
	const float c_selectScaleSpeed = 0.02f;//大きさが変わるスピード
	const float c_nextScaleMax = 1.2f;     //最大の大きさ
	const float c_nextScaleMin = 0.8f;     //最初の大きさ
	bool  m_nextScaleFlag = false;
	float  m_nextScale = 1.0f;


	const float numberScale = 128.0f;     //数字の大きさ

	//ボタン
	SpriteData  m_buttonGraph;
	int  m_buttonTime = 0;

	//音データ
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
	SoundData  m_buttonSE = {};                 //ボタンSE
};