#pragma once
#include "StegeObject.h"
/// <summary>
/// 置物のOBJ
/// </summary>
class FigurineOBJ
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FigurineOBJ();
	//デスコンストラクタ
	~FigurineOBJ();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(StageData* stageObj, const bool shadowFlag);
private:
	//壁OBJ
	ObjectData m_wallOBJ;
	//枯れ木OBJ
	ObjectData m_deadTree;
	//岩
	ObjectData m_stone;
	//氷のアーチ
	ObjectData m_iceArch;
	//看板
	ObjectData m_signboard;
	TextureData m_tutorialGraph[2] = {};
	int m_tutorialNum = SIGNBOARD1;		//チュートリアルの基本値

};

