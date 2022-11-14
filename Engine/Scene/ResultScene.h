#include"Singleton.h"
#include <Object.h>
#include<memory>
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
	void Draw();

	void ShadowDraw();
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	ObjectData penginObj;
	PSR objectPsr = {};
	ObjectData fishObj;
	ObjectData floorObj;

	//壊れた箱リザルト
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;

	//ボタン
	SpriteData buttonGraph;
	int buttonTime = 0;
};