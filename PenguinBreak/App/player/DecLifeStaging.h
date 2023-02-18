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
	void Update(int decTime, bool gameoverFlag);
	//描画
	void Draw(bool gameoverFlag, int gameoverNum = 0);

	void Reset();
private:
	SpriteData decGraph;
	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	const float gameoverColor = 0.75f;

	bool isStart = false;

	const float speed = 0.02f;


	//ゲームオーバー時の
	static	const int charNum = 7;
	SpriteData gameoverGraph[charNum];
	SpriteData selectGraph;

	SpriteData gameoverSelect[2];

	bool gameoverStartFlag = false;
	const float gameoverTimeMax = 100.0f;
	int gameoverTime = 0;
	//セレクト時の演出
	bool selectScaleFlag = false;
	float selectScale = 1.0f;

	//ゲームオーバーの文字の変化
	float charColor[charNum] = {};
	bool charFlag[charNum] = {};
	float charPos[charNum] = {};
	bool charPosFlag[charNum] = {};
	const float charPosSpeed = 0.45f;
};

