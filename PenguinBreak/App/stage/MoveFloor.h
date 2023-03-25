#pragma once
#include"./StegeObject.h"

//�O�֐i�ނ����֐i�ނ�
enum class MoveType
{
	MOVEFRONT,
	MOVEBACK,
};
/// <summary>
/// �������N���X
/// </summary>
class MoveFloor
{

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MoveFloor();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~MoveFloor();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="floorData">���f�[�^</param>
	void Update(StageData* floorData);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="floorData">���f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(StageData* floorData, const bool shadowFlag);
private:
	ObjectData m_moveFloorOBJ;						//��OBJ
	const Vec3 c_speed = { 0.0f,0.0f,0.5f };		//�����i�ރX�s�[�h
	const float c_timeMax = 150.0f;					//�؂�ւ���܂ł̎���
	const Vec3 c_OBJScale = { 25.0f,25.0f,25.0f };	//OBJ�X�P�[��
};

