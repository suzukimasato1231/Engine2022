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
	SpriteData m_decGraph;						//暗転画像
	SpriteData m_gameoverGraph[charNum];			//ゲームオーバー文字画像
	SpriteData m_selectGraph;						//セレクト画像
	SpriteData m_gameoverSelect[2];				//セレクト文字画像
	const Vec2 c_framSize = { 349.0f, 143.0f };	//フレームサイズ
	const Vec2 c_selectSize = { 334.0f,128.0f };	//セレクトサイズ

	Vec4 m_color = { 1.0f,1.0f,1.0f,1.0f };		//暗転色
	const float c_colorMax = 1.0f;				//色の最大
	bool m_isStart = false;						//ゲームオーバー演出開始したか
	const float c_blackColorMax = 0.75f;			//最大の暗さ
	const float c_blackSpeed = 0.02f;				//暗くなっていく速度
	bool m_gameoverStartFlag = false;				//ゲームオーバー
	const float c_gameoverTimeMax = 100.0f;		//暗転最大時間
	int m_gameoverTime = 0;						//暗転時間
	bool m_selectScaleFlag = false;				//セレクト小さいか大きいか
	float m_selectScale = 1.0f;					//セレクトの大きさ
	//ゲームオーバーの文字の変化
	float m_charColor[charNum] = {};				//文字の色
	bool m_charFlag[charNum] = {};				//透明かどうか
	float m_charPos[charNum] = {};				//文字の位置
	bool m_charPosFlag[charNum] = {};				//文字が上がるか下がるか
	const float c_charPosSpeed = 0.45f;			//文字が動くスピード
	const float c_scaleMax = 1.3f;				//文字の最大の大きさ
	const float c_scaleMin = 1.0f;				//文字の最小の大きさ
	const float c_scaleSpeed = 0.02f;				//文字の大きさが変わるスピード
	const float c_charColorSpeed = 0.01f;			//文字の色が変わるスピード
	const float c_charPosMax = 10.0f;				//文字の最大変化量
};

