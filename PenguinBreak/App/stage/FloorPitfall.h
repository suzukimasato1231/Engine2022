#pragma once
#include"./StegeObject.h"
/// <summary>
/// 回転床
/// </summary>
class FloorPitfall
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FloorPitfall();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~FloorPitfall();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="floorData">床データ</param>
	void Update(Floor* floorData);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="floorData">床データ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(Floor* floorData, const bool shadowFlag);
private:
	ObjectData m_pitfallOBJ;
	int m_pitfallGraph = 0;
	const int c_pitfallTime = 70;
};

