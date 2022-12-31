#include <Object.h>
#include<memory>
#include"FBXObject3d.h"

enum ResultNext
{
	ResultNextStage,
	ResultSelect,
};


class ResultScene
{
private:

public:
	ResultScene();

	~ResultScene();

	void Initialize();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(const int stageNum);

	void Delete();

	void ShadowDraw();

	bool GetScene() { return nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	//ゴール時の演出ハンドサイン
	Model* penginModel = nullptr;
	std::unique_ptr<FBXObject3d> penginHandFbx[2];

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
};