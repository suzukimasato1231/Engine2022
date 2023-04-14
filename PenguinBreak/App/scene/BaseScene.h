#pragma once

class SceneManager;


class BaseScene
{
public:
	virtual ~BaseScene() = default;
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	virtual void Init(int stageNum) = 0;
	/// <summary>
	/// XV
	/// </summary>
	virtual void Update(int& stageNum, int m_breakBox[]) = 0;
	/// <summary>
	/// •`‰æ
	/// </summary>
	virtual void Draw(const int stageNum) = 0;
	/// <summary>
	/// ‰e•`‰æ
	/// </summary>
	virtual void ShadowDraw() = 0;

	virtual void SecondDraw() = 0;

	virtual void Finalize() = 0;

	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

	bool GetSceneFlag() { return m_sceneFlag; };

	int GetSceneNum() { return m_sceneNum; };

protected:
	bool m_sceneFlag = false;

	int m_sceneNum = 0;

	SceneManager* sceneManager_ = nullptr;
};

