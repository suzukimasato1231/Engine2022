#pragma once
#include"Object.h"
#include<vector>
class FishBox
{
private:
	struct FishData
	{
		Vec3 position = {};
		Vec3 startPosition = {};
		float fishTime = 0.0f;
		bool endFlag = false;
		PSR psr = {};
	};
public:

	FishBox();

	~FishBox();
	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update(Vec3 pPos);
	//•`‰æˆ—
	void Draw();
	//ì¬ˆ—
	void Create(Vec3 pos);

	void Delete();
private:
	ObjectData fishOBJ;
	std::vector<FishData*>fishData;
	//‘å‚«‚³
	const Vec3 scale = { 1.8f,1.8f,1.8f };
	//UI‚Ì‹›‚ÌˆÊ’u
	const Vec3 fishGoalPos = { -70.0f,50.0f,10.0f };
	//ˆÚ“®‚·‚éŠÔ
	const float time = 50.0f;
};

