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
	SpriteData decGraph;						//�Ó]�摜
	SpriteData gameoverGraph[charNum];			//�Q�[���I�[�o�[�����摜
	SpriteData selectGraph;						//�Z���N�g�摜
	SpriteData gameoverSelect[2];				//�Z���N�g�����摜
	const Vec2 framSize = { 349.0f, 143.0f };	//�t���[���T�C�Y
	const Vec2 selectSize = { 334.0f,128.0f };	//�Z���N�g�T�C�Y

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };		//�Ó]�F
	const float colorMax = 1.0f;				//�F�̍ő�
	bool isStart = false;						//�Q�[���I�[�o�[���o�J�n������
	const float blackColorMax = 0.75f;			//�ő�̈Â�
	const float blackSpeed = 0.02f;				//�Â��Ȃ��Ă������x
	bool gameoverStartFlag = false;				//�Q�[���I�[�o�[
	const float gameoverTimeMax = 100.0f;		//�Ó]�ő厞��
	int gameoverTime = 0;						//�Ó]����
	bool selectScaleFlag = false;				//�Z���N�g���������傫����
	float selectScale = 1.0f;					//�Z���N�g�̑傫��
	//�Q�[���I�[�o�[�̕����̕ω�
	float charColor[charNum] = {};				//�����̐F
	bool charFlag[charNum] = {};				//�������ǂ���
	float charPos[charNum] = {};				//�����̈ʒu
	bool charPosFlag[charNum] = {};				//�������オ�邩�����邩
	const float charPosSpeed = 0.45f;			//�����������X�s�[�h
	const float scaleMax = 1.3f;				//�����̍ő�̑傫��
	const float scaleMin = 1.0f;				//�����̍ŏ��̑傫��
	const float scaleSpeed = 0.02f;				//�����̑傫�����ς��X�s�[�h
	const float charColorSpeed = 0.01f;			//�����̐F���ς��X�s�[�h
	const float charPosMax = 10.0f;				//�����̍ő�ω���
};

