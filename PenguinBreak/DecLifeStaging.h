#pragma once
#include"Sprite.h"
/// <summary>
/// �v���C���[�����S�����Ƃ��̉��o
/// </summary>
class DecLifeStaging
{
public:
	//�C���X�g���N�^
	DecLifeStaging();
	//�f�X�g���N�^
	~DecLifeStaging();
	//������
	void Init();
	//�X�V
	void Update(int decTime, bool gameoverFlag);
	//�`��
	void Draw(bool gameoverFlag, int gameoverNum = 0);

	void Reset();
private:
	SpriteData decGraph;
	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	const float gameoverColor = 0.75f;

	bool isStart = false;

	const float speed = 0.02f;


	//�Q�[���I�[�o�[����
	SpriteData gameoverGraph[7];
	SpriteData selectGraph;

	SpriteData gameoverSelect[2];

	bool gameoverStartFlag = false;
	const float gameoverTimeMax = 100.0f;
	int gameoverTime = 0;
	//�Z���N�g���̉��o
	bool selectScaleFlag = false;
	float selectScale = 1.0f;

	//�Q�[���I�[�o�[�̕����̕ω�
	float charColor[7] = {};
	bool charFlag[7] = {};
	float charPos[7] = {};
	bool charPosFlag[7] = {};
	const float charPosSpeed = 0.45f;
};

