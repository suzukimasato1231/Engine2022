#pragma once
#include"./StegeObject.h"
/// <summary>
/// 回転床
/// </summary>
class FloorPitfall
{
private:
	/// <summary>
	/// 開いているか閉じているか
	/// </summary>
	enum PitfallOpenClose
	{
		PITFALLCLOSE,
		PITFALLOPEN,
	};
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
	ObjectData m_pitfallOBJ;						//床OBJ
	int m_pitfallGraph = 0;							//床画像
	const int c_pitfallTime = 70;					//回転時間
	const int c_pitfallSpeed = 18;					//回転速度
	const Vec3 c_pitfallScale = { 25.0f,5.0f,25.0f };//	描画スケール
};

