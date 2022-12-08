#include <Sprite.h>
/// <summary>
/// メニュークラス
/// </summary>
class Menu
{
public:
	//コンストラクタ
	Menu();
	//デスコンストラクタ
	~Menu();
	//初期化
	void Init();
	//更新
	void Update(bool& menuFlag, bool& changeScene, int& sceneNum);
	//描画
	void Draw(const bool gameoverFlag);

	void Reset();
private:
	//メニュー関連
	SpriteData menuButton;
	SpriteData menuFream;
	SpriteData menuRetry;
	SpriteData menuVolum;
	SpriteData menuStageSelect;
	SpriteData menuFish;
	int menuNum = 0;
	//メニューの強調
	bool menuTimeFlag = false;
	float menuScale = 1.0f;
	//イージング（メニュー）
	const Vec3 c_start = { 1500.0f,300.0f,0.0f };
	const Vec3 c_end = { 950.0f,300.0f,0.0f };
	Vec3 menuPos = { 0.0f,0.0f ,0.0f };
	bool menuEasingFlag = false;
	//出てくるとき
	const float c_startTimeMax = 20.0f;
	float m_startTime = 0.0f;

	//音
	SpriteData menuAudioFream;
	SpriteData menuAudioVolum;
	SpriteData menuAudioLandmark;
	//音量調整フラグ
	bool audioFlag = false;
	
	const float volumMax = 0.10f;
	const float volumMin = 0.0f;
	float volum = 0.02f;

};