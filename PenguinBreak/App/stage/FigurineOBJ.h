#pragma once
#include "StegeObject.h"
/// <summary>
/// �u����OBJ
/// </summary>
class FigurineOBJ
{
public:
	//�R���X�g���N�^
	FigurineOBJ();

	//�f�X�R���X�g���N�^
	~FigurineOBJ();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
private:
	//��OBJ
	ObjectData wallOBJ;
	//�͂��OBJ
	ObjectData deadTree;
	//��
	ObjectData stone;

};

