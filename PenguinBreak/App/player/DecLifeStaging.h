#pragma once
#include"Sprite.h"
/// <summary>
/// プレイヤーが死亡したときの演出
/// </summary>
class DecLifeStaging
{
private:
	static	const int charNum = 7;				//文字数
	enum ChangeScene
	{
		RETRY = 1,
		SELECT,
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DecLifeStaging();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~DecLifeStaging();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="decTime"></param>
	/// <param name="gameoverFlag">ゲームオーバーフラグ</param>
	void Update(const int decTime, const bool gameoverFlag);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="gameoverFlag">ゲームオーバーフラグ</param>
	/// <param name="gameoverNum"></param>
	void Draw(bool gameoverFlag, int gameoverNum = 0);
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
private:
	/// <summary>
	/// 暗転処理
	/// </summary>
	void Blackout(const int decTime, const bool gameoverFlag);
	/// <summary>
	/// 文字の動き
	/// </summary>
	void LetterMove();
private:
	SpriteData decGraph;						//暗転画像
	SpriteData gameoverGraph[charNum];			//ゲームオーバー文字画像
	SpriteData selectGraph;						//セレクト画像
	SpriteData gameoverSelect[2];				//セレクト文字画像
	const Vec2 framSize = { 349.0f, 143.0f };	//フレームサイズ
	const Vec2 selectSize = { 334.0f,128.0f };	//セレクトサイズ

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };		//暗転色
	const float colorMax = 1.0f;				//色の最大
	bool isStart = false;						//ゲームオーバー演出開始したか
	const float blackColorMax = 0.75f;			//最大の暗さ
	const float blackSpeed = 0.02f;				//暗くなっていく速度
	bool gameoverStartFlag = false;				//ゲームオーバー
	const float gameoverTimeMax = 100.0f;		//暗転最大時間
	int gameoverTime = 0;						//暗転時間
	bool selectScaleFlag = false;				//セレクト小さいか大きいか
	float selectScale = 1.0f;					//セレクトの大きさ
	//ゲームオーバーの文字の変化
	float charColor[charNum] = {};				//文字の色
	bool charFlag[charNum] = {};				//透明かどうか
	float charPos[charNum] = {};				//文字の位置
	bool charPosFlag[charNum] = {};				//文字が上がるか下がるか
	const float charPosSpeed = 0.45f;			//文字が動くスピード
	const float scaleMax = 1.3f;				//文字の最大の大きさ
	const float scaleMin = 1.0f;				//文字の最小の大きさ
	const float scaleSpeed = 0.02f;				//文字の大きさが変わるスピード
	const float charColorSpeed = 0.01f;			//文字の色が変わるスピード
	const float charPosMax = 10.0f;				//文字の最大変化量
};

