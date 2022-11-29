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
	void Update(int decTime);
	//�`��
	void Draw(bool gameoverFlag);

	void Reset();
private:
	SpriteData decGraph;
	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	bool isStart = false;

	const float speed = 0.02f;


};

