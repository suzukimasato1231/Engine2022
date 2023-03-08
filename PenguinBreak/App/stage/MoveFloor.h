#pragma once
#include"./StegeObject.h"
/// <summary>
/// 動く床クラス
/// </summary>
class MoveFloor
{
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
	ObjectData m_moveFloorOBJ;

	Vec3 m_speed = { 0.0f,0.0f,0.5f };
};

