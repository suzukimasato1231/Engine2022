#pragma once
#include "StegeObject.h"
/// <summary>
/// 置物のOBJ
/// </summary>
class FigurineOBJ
{
public:
	//コンストラクタ
	FigurineOBJ();

	//デスコンストラクタ
	~FigurineOBJ();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
private:
	//壁OBJ
	ObjectData wallOBJ;
	//枯れ木OBJ
	ObjectData deadTree;
	//岩
	ObjectData stone;

};

