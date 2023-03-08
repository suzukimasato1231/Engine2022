#include <Object.h>
#include<memory>
#include"FBXObject3d.h"
#include<Audio.h>
/// <summary>
/// シーン移動
/// </summary>
enum ResultNext
{
	ResultNextStage,
	ResultSelect,
};

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene
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
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// ループ初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageNum">ステージ</param>
	void Draw(const int stageNum);
	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowDraw();

	inline bool GetScene() { return  m_nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData  m_resultOBJ;
	int  m_resultTime = 0;

	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model>  m_penginModel;
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;

	PSR  m_objectPsr = {};
	ObjectData  m_fishObj;
	ObjectData  m_floorObj;

	//壊れた箱リザルト
	SpriteData  m_uiNumber[10];
	SpriteData  m_uiSlash;
	SpriteData  m_boxGraph;

	SpriteData  m_clearGraph;
	SpriteData  m_selectGraph;
	SpriteData  m_nextGraph;
	int  m_nextScene = 0;
	const float c_nextScaleMax = 1.2f;
	const float c_nextScaleMin = 0.8f;
	bool  m_nextScaleFlag = false;
	float  m_nextScale = 1.0f;

	//ボタン
	SpriteData  m_buttonGraph;
	int  m_buttonTime = 0;

	//音データ
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
};