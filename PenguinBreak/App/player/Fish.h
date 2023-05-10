#pragma once
class FishClass
{
public: 
	/// <summary>
	/// コンストラクト
	/// </summary>
	FishClass();
	/// <summary>
	/// デスコンストラクト
	/// </summary>
	~FishClass();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 魚の更新
	/// </summary>
	void Update(bool& m_changeBreakFlag, int& m_remainLives);

	int GetFishNum()const { return m_fishNum; }
private:
	bool m_fishFlag = false;			//魚を獲得したか
	int m_fishNum = 0;					//魚獲得数
	const int c_fishMax = 100;			//最大獲得数
	const int c_fishPlas = 5;			//一回の獲得数
};

