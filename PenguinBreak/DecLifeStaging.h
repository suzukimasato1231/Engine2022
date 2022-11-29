#pragma once
#include"Sprite.h"
/// <summary>
/// プレイヤーが死亡したときの演出
/// </summary>
class DecLifeStaging
{
public:
	//インストラクタ
	DecLifeStaging();
	//デストラクタ
	~DecLifeStaging();
	//初期化
	void Init();
	//更新
	void Update(int decTime);
	//描画
	void Draw(bool gameoverFlag);

	void Reset();
private:
	SpriteData decGraph;
	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	bool isStart = false;

	const float speed = 0.02f;


};

