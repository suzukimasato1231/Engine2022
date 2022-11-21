#pragma once
#include"Object.h"
#include"../PenguinBreak/App/stage/StegeObject.h"
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

	void Update(Vec3 pPos, Vec3 pos, Vec3 angle, Vec3 scale);

	void Draw(Vec3 pPos);

	void ChangeFlag() { isPointFlag = false; }
private:
	ObjectData dropPointOBJ = {};

	int dropPointGraph = 0;

	PSR dropPointPSR = {};

	Vec3 position = {};

	bool isPointFlag = false;

	float groundDistance = 0.0f;
};

