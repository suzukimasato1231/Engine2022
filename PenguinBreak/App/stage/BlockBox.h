#pragma once
#include"StegeObject.h"
#include"Object.h"
#include"LoadCSV.h"
/// <summary>
/// ���N���X
/// </summary>
class BlockBox
{
public:
	BlockBox() {};

	~BlockBox() {};
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �v���C���[�Ɣ��̓����蔻��
	/// </summary>
	/// <param name="stageObj">�I�u�W�F�N�g���</param>
	/// <param name="X">X���̈ʒu</param>
	/// <param name="Z">Z���̈ʒu</param>
	void PlayerHit(StageOBJ* stageObj, const int X, const int Z);
	/// <summary>
	/// �X�s���Ɣ��̓����蔻��
	/// </summary>
	/// <param name="stageObj">�I�u�W�F�N�g���</param>
	/// <param name="X">X���̈ʒu</param>
	/// <param name="Z">Z���̈ʒu</param>
	void PlayerSpinHit(StageOBJ* stageObj, const int X, const int Z);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <returns></returns>
	void Draw(StageOBJ* stageObj, bool shadowFlag);
private:
	/// <summary>
	/// ���e���o
	/// </summary>
	void BombUpdate();
public:
	StageOBJ* GetObj_Data() { return obj_data; }

	StageOBJ GetObj_Data(int i) { return obj_data[i]; }

	int GetBox_Count() { return box_count; }

	bool GetIs_Hit() { return is_hit; }

	StageOBJ GetObj_Spin(int i) { return obj_spin[i]; }

	int GetSpin_Count() { return spin_count; }

	bool GetIs_Spin() { return is_spin; }

	Vec3 GetBoxScale() { return breakBoxScale; }
private:
	ObjectData breakBoxOBJ = {};
	//���̑傫��
	const Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
	//���锠�̉摜
	int normalBoxGraph = 0;
	//�ł����̉摜
	int hardBoxGraph = 0;
	//�W�����v�̔��̉摜
	int jumpBoxgraph = 0;
	//���e�̔��̉摜
	int bombBoxGraph = 0;
	Vec3 bombBoxAngle = {};							//���e�p�x
	const Vec3 bombSpeedAngle = { 0.0f,2.0f,0.0f };	//��]���x
	bool bombBoxFlag = false;						//���e���o�t���O
	int bombTime = 0;								//�J�X����
	const int bombTimeMax = 45;						//��]���ԍő�
	const Vec3 bombPlasSpeed = {0.0f,0.2f,0.0f};	//���˂鑬�x
	Vec3 bombPlas = {0.0f,0.0f,0.0f};				//���e���̒��˂鋗��

	//�ڐG���̔���Ɏg����
	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[5] = {};
	//�X�s���̓����蔻��Ɏg����
	bool is_spin = false;
	int spin_count = 0;
	StageOBJ obj_spin[5] = {};
};

