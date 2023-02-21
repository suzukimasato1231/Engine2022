#pragma once
#include"StegeObject.h"
#include"Object.h"
#include"LoadCSV.h"
/// <summary>
/// 箱クラス
/// </summary>
class BlockBox
{
public:
	BlockBox() {};

	~BlockBox() {};

	void Init();

	void PlayerHit(StageOBJ* stageObj, const int X, const int Z);

	void PlayerSpinHit(StageOBJ* stageObj, const int X, const int Z);

	void Update();

	void Draw(StageOBJ* stageObj, bool shadowFlag);

	static StageOBJ SetBox(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type);
public:
	StageOBJ* GetObj_Data() { return obj_data; }

	StageOBJ GetObj_Data(int i) { return obj_data[i]; }

	int GetBox_Count() { return box_count; }

	bool GetIs_Hit() { return is_hit; }

	StageOBJ GetObj_Spin(int i) { return obj_spin[i]; }

	int GetSpin_Count() { return spin_count; }

	bool GetIs_Spin() { return is_spin; }

	Vec3 GetBoxScale() { return breakBoxScale; }
private:
	ObjectData breakBoxOBJ = {};
	//壊れる箱の画像
	int normalBoxGraph = 0;
	//固い箱の画像
	int hardBoxGraph = 0;
	//ジャンプの箱の画像
	int jumpBoxgraph = 0;
	//爆弾の箱の画像
	int bombBoxGraph = 0;
	//箱の大きさ
	const Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };

	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[5] = {};

	bool is_spin = false;
	int spin_count = 0;
	StageOBJ obj_spin[5] = {};
};

