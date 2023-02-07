#pragma once
#include"StegeObject.h"
#include"Object.h"
#include"LoadCSV.h"
class BlockBox
{
public:
	BlockBox() {};

	~BlockBox() {};

	void Init();

	void PlayerHit(StageOBJ* stageObj, const int X, const int Z);

	void Update();

	void Draw(StageOBJ* stageObj, bool shadowFlag);

	static StageOBJ SetBox(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map, int type);
public:
	StageOBJ* GetObj_Data() { return obj_data; }

	StageOBJ GetObj_Data(int i) { return obj_data[i]; }

	int GetBox_Count() { return box_count; }

	bool GetIs_Hit() { return is_hit; }

	Vec3 GetBoxScale() { return breakBoxScale; }
private:
	ObjectData breakBoxOBJ = {};
	//‰ó‚ê‚é” ‚Ì‰æ‘œ
	int normalBoxGraph = 0;
	//ŒÅ‚¢” ‚Ì‰æ‘œ
	int hardBoxGraph = 0;
	//ƒWƒƒƒ“ƒv‚Ì” ‚Ì‰æ‘œ
	int jumpBoxgraph = 0;
	//” ‚Ì‘å‚«‚³
	const Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };

	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[4] = {};
};

