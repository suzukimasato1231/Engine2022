#pragma once
#include"Sprite.h"
/// <summary>
/// �v���C���[�����S�����Ƃ��̉��o
/// </summary>
class DecLifeStaging
{
private:
	static	const int charNum = 7;				//������
	enum ChangeScene
	{
		RETRY = 1,
		SELECT,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DecLifeStaging();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~DecLifeStaging();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="decTime"></param>
	/// <param name="gameoverFlag">�Q�[���I�[�o�[�t���O</param>
	void Update(const int decTime, const bool gameoverFlag);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="gameoverFlag">�Q�[���I�[�o�[�t���O</param>
	/// <param name="gameoverNum"></param>
	void Draw(bool gameoverFlag, int gameoverNum = 0);
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();
private:
	/// <summary>
	/// �Ó]����
	/// </summary>
	void Blackout(const int decTime, const bool gameoverFlag);
	/// <summary>
	/// �����̓���
	/// </summary>
	void LetterMove();
private:
	SpriteData m_decGraph;						//�Ó]�摜
	SpriteData m_gameoverGraph[charNum];			//�Q�[���I�[�o�[�����摜
	SpriteData m_selectGraph;						//�Z���N�g�摜
	SpriteData m_gameoverSelect[2];				//�Z���N�g�����摜
	const Vec2 c_framSize = { 349.0f, 143.0f };	//�t���[���T�C�Y
	const Vec2 c_selectSize = { 334.0f,128.0f };	//�Z���N�g�T�C�Y

	Vec4 m_color = { 1.0f,1.0f,1.0f,1.0f };		//�Ó]�F
	const float c_colorMax = 1.0f;				//�F�̍ő�
	bool m_isStart = false;						//�Q�[���I�[�o�[���o�J�n������
	const float c_blackColorMax = 0.75f;			//�ő�̈Â�
	const float c_blackSpeed = 0.02f;				//�Â��Ȃ��Ă������x
	bool m_gameoverStartFlag = false;				//�Q�[���I�[�o�[
	const float c_gameoverTimeMax = 100.0f;		//�Ó]�ő厞��
	int m_gameoverTime = 0;						//�Ó]����
	bool m_selectScaleFlag = false;				//�Z���N�g���������傫����
	float m_selectScale = 1.0f;					//�Z���N�g�̑傫��
	//�Q�[���I�[�o�[�̕����̕ω�
	float m_charColor[charNum] = {};				//�����̐F
	bool m_charFlag[charNum] = {};				//�������ǂ���
	float m_charPos[charNum] = {};				//�����̈ʒu
	bool m_charPosFlag[charNum] = {};				//�������オ�邩�����邩
	const float c_charPosSpeed = 0.45f;			//�����������X�s�[�h
	const float c_scaleMax = 1.3f;				//�����̍ő�̑傫��
	const float c_scaleMin = 1.0f;				//�����̍ŏ��̑傫��
	const float c_scaleSpeed = 0.02f;				//�����̑傫�����ς��X�s�[�h
	const float c_charColorSpeed = 0.01f;			//�����̐F���ς��X�s�[�h
	const float c_charPosMax = 10.0f;				//�����̍ő�ω���
};

