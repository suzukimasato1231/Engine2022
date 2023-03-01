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

	inline bool GetScene() { return nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	//ゴール時の演出ハンドサイン
	std::unique_ptr<Model> penginModel;
	std::unique_ptr<FBXObject3d> penginHandFbx;

	PSR objectPsr = {};
	ObjectData fishObj;
	ObjectData floorObj;

	//壊れた箱リザルト
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;

	SpriteData clearGraph;
	SpriteData selectGraph;
	SpriteData nextGraph;
	int nextScene = 0;
	const float nextScaleMax = 1.2f;
	const float nextScaleMin = 0.8f;
	bool nextScaleFlag = false;
	float nextScale = 1.0f;

	//ボタン
	SpriteData buttonGraph;
	int buttonTime = 0;

	//音データ
	SoundData decisionSE = {};
	SoundData selectSE = {};
};