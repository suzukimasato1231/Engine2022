#pragma once
#include"Menu.h"
/// <summary>
/// UI�N���X
/// </summary>
class UI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UI();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~UI();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="fishNum">����</param>
	/// <param name="clearFlag">�N���A�t���O</param>
	/// <param name="changeScene">�`�F���W�t���O</param>
	/// <param name="sceneNum">�V�[����</param>
	void Update(int fishNum, bool clearFlag, bool& changeScene, int& sceneNum);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pLives">�c�@��</param>
	/// <param name="gameoverFlag">�Q�[���I�[�o�[�t���O</param>
	void Draw(const int pLives, const  bool gameoverFlag);
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();

	bool GetMenuFlag() { return m_menuFlag; }
private:
	//�Q�[�����UI
	SpriteData m_boxGraph;

	SpriteData m_playerIcon;

	SpriteData m_fishGraph;

	SpriteData m_uiNumber[10];
	SpriteData m_uiSlash;

	//���j���[
	Menu m_menu;
	bool m_menuFlag = false;

	//���o(�Q�[�����)
	float m_fishPosPlas = 0.0f;
	const int c_stagingTimeMax = 20;
	const float c_stagingScaleMax = 1.5f;
	float m_stagingScale[4] = { 0.0f,0.0f,0.0f,0.0f };
	int m_stagingTime[4] = {};
	bool m_stagingFlag[4] = {};
	//�󂵂����̐�
	int m_breakNumber = 1, m_breakRemain = 1;
	//�ő唠�̐�
	int m_breakNumberMax = 1, m_breakRemainMax = 1;
	//���̐�
	int m_fishNumber = 1, m_fishRemain = 1;
};

