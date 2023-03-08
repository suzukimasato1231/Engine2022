#pragma once
#include"./StegeObject.h"
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
	void Update(Floor* floorData);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="floorData">���f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(Floor* floorData, const bool shadowFlag);
private:
	ObjectData m_moveFloorOBJ;

	Vec3 m_speed = { 0.0f,0.0f,0.5f };
};

