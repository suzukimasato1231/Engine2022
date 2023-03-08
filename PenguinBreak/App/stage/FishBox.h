#pragma once
#include"Object.h"
#include<vector>
/// <summary>
/// 魚クラス
/// </summary>
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
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FishBox();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~FishBox();
	//初期化処理
	void Init();
	//更新処理
	void Update(const Vec3 &pPos);
	//描画処理
	void Draw();
	//作成処理
	void Create(const Vec3 &pos);

	void Delete();
private:
	ObjectData fishOBJ;
	std::vector<FishData*>fishData;
	//大きさ
	const Vec3 scale = { 1.8f,1.8f,1.8f };
	//UIの魚の位置
	const Vec3 fishGoalPos = { -70.0f,50.0f,10.0f };
	//移動する時間
	const float time = 50.0f;
};

