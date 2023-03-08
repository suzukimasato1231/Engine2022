#pragma once
#include"Object.h"
#include<vector>
/// <summary>
/// 魚クラス
/// </summary>
class FishBox
{
private:
	/// <summary>
	/// 魚データ
	/// </summary>
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
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="pPos">プレイヤー位置</param>
	void Update(const Vec3 &pPos);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 作成処理
	/// </summary>
	/// <param name="pos">作成位置</param>
	void Create(const Vec3 &pos);
	/// <summary>
	/// データ消去
	/// </summary>
	void Delete();
private:
	ObjectData m_fishOBJ;
	std::vector<FishData*>fishData;
	//大きさ
	const Vec3 c_scale = { 1.8f,1.8f,1.8f };
	//UIの魚の位置
	const Vec3 c_fishGoalPos = { -70.0f,50.0f,10.0f };
	//移動する時間
	const float c_time = 50.0f;
};

