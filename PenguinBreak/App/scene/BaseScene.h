#pragma once
class BaseScene
{
public:
	virtual ~BaseScene() = default;
	/// <summary>
	/// ������
	/// </summary>
	virtual void Init(int stageNum) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update(int& stageNum, const int m_breakBox[]) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw(const int stageNum) = 0;
	/// <summary>
	/// �e�`��
	/// </summary>
	virtual void ShadowDraw() = 0;

	virtual void SecondDraw() = 0;

	virtual void Finalize() = 0;

	bool GetSceneFlag() { return m_sceneFlag; };

	int GetSceneNum() { return m_sceneNum; };

protected:
	bool m_sceneFlag = false;

	int m_sceneNum = 0;
};

