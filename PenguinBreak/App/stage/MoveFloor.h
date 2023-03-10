#pragma once
#include"./StegeObject.h"
/// <summary>
/// 動く床クラス
/// </summary>
class MoveFloor
{
private:
	//前へ進むか後ろへ進むか
	enum MoveUpDown
	{
		MOVEFRONT,
		MOVEBACK,
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveFloor();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~MoveFloor();
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
	ObjectData m_moveFloorOBJ;						//床OBJ
	const Vec3 c_speed = { 0.0f,0.0f,0.5f };		//床が進むスピード
	const float c_timeMax = 150.0f;					//切り替えるまでの時間
	const Vec3 c_OBJScale = { 25.0f,25.0f,25.0f };	//OBJスケール
};

