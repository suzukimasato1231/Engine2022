#include"Singleton.h"
#include <Object.h>

class ResultScene 
{
private:

public:
	void Initialize();

	void Init();

	void Update();

	void Draw();
private:
	ObjectData resultOBJ;

	int resultTime = 0;


	//壊れた箱リザルト
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;


	//ボタン
	SpriteData buttonGraph;
	int buttonTime = 0;
};