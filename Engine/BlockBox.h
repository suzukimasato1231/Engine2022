#pragma once
#include"./StegeObject.h"
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

	static StageOBJ SetBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type);
public:
	StageOBJ* GetObj_Data() { return obj_data; }

	StageOBJ GetObj_Data(int i) { return obj_data[i]; }

	int GetBox_Count() { return box_count; }

	bool GetIs_Hit() { return is_hit; }
private:
	ObjectData breakBoxOBJ = {};
	int normalBoxGraph = 0;		//���锠�̉摜
	int hardBoxGraph = 0;		//�ł����̉摜
	int jumpBoxgraph = 0;		//�W�����v�̔��̉摜

	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[4] = {};
};

