#pragma once
#include"StegeObject.h"
#include"Object.h"
/// <summary>
/// ���N���X
/// </summary>
class BlockBox
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BlockBox() {};
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
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
	void PlayerHit(StageData* stageObj);
	/// <summary>
	/// �X�s���Ɣ��̓����蔻��
	/// </summary>
	/// <param name="stageObj">�I�u�W�F�N�g���</param>
	/// <param name="X">X���̈ʒu</param>
	/// <param name="Z">Z���̈ʒu</param>
	void PlayerSpinHit(StageData* stageObj);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <returns></returns>
	void Draw(StageData* stageObj, bool shadowFlag);
private:
	/// <summary>
	/// ���e���o
	/// </summary>
	void BombUpdate();
public:
	StageData* GetObj_Data() { return m_obj_data; }

	StageData GetObj_Data(int i) { return m_obj_data[i]; }

	int GetBox_Count() { return m_box_count; }

	bool GetIs_Hit() { return m_is_hit; }

	StageData GetObj_Spin(int i) { return m_obj_spin[i]; }

	int GetSpin_Count() { return m_spin_count; }

	bool GetIs_Spin() { return m_is_spin; }

	Vec3 GetBoxScale() { return c_breakBoxScale; }
private:
	ObjectData m_breakBoxOBJ = {};
	//���̑傫��
	const Vec3 c_breakBoxScale = { 20.0f,20.0f,20.0f };
	//���锠�̉摜
	TextureData m_normalBoxGraph = {};
	//�ł����̉摜
	TextureData m_hardBoxGraph = {};
	//�W�����v�̔��̉摜
	TextureData m_jumpBoxgraph = {};
	//���e�̔��̉摜
	TextureData m_bombBoxGraph = {};
	Vec3 m_bombBoxAngle = {};							//���e�p�x
	const Vec3 c_bombSpeedAngle = { 0.0f,2.0f,0.0f };	//��]���x
	bool m_bombBoxFlag = false;							//���e���o�t���O
	int m_bombTime = 0;									//�J�X����
	const int c_bombTimeMax = 45;						//��]���ԍő�
	const Vec3 c_bombPlasSpeed = {0.0f,0.2f,0.0f};		//���˂鑬�x
	Vec3 m_bombPlas = {0.0f,0.0f,0.0f};					//���e���̒��˂鋗��
	//�ő�q�b�g��
	const int hitMax = 4;
	//�ڐG���̔���Ɏg����
	bool m_is_hit = false;
	int m_box_count = 0;
	StageData m_obj_data[5] = {};
	//�X�s���̓����蔻��Ɏg����
	bool m_is_spin = false;
	int m_spin_count = 0;
	StageData m_obj_spin[5] = {};
};

