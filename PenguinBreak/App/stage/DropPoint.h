#pragma once
#include"Object.h"
#include"../stage/StegeObject.h"
/// <summary>
/// 落下地点
/// </summary>
class DropPoint
{
public:
	//コンストラクタ
	DropPoint();

	~DropPoint();

	void Init();

	void Update(const Vec3 &pPos, const Vec3 &pos, const Vec3 &angle, const Vec3 &scale);

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

