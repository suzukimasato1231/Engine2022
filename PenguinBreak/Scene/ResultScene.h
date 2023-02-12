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

	~ResultScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	//ループ初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(const int stageNum);
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
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
	Model* penginModel = nullptr;
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