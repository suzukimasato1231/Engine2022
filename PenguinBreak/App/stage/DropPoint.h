#pragma once
#include"Object.h"
#include"../stage/StegeObject.h"
/// <summary>
/// 落下地点
/// </summary>
class DropPoint
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DropPoint();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~DropPoint();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	///	更新
	/// </summary>
	/// <param name="pPos">プレイヤー座標</param>
	/// <param name="pos">床座標</param>
	/// <param name="angle">角度</param>
	/// <param name="scale">大きさ</param>
	void Update(const Vec3 &pPos, const Vec3 &pos, const Vec3 &angle, const Vec3 &scale);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pPos">座標</param>
	void Draw(const Vec3 &pPos);

	void ChangeFlag() { isPointFlag = false; }
private:
	ObjectData dropPointOBJ = {};

	int dropPointGraph = 0;

	PSR dropPointPSR = {};

	Vec3 position = {};

	bool isPointFlag = false;

	float groundDistance = 0.0f;
};

