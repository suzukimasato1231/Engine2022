#pragma once
#include"StegeObject.h"
/// <summary>
/// �댯���N���X
/// </summary>
class DangerFish
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DangerFish();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~DangerFish();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	void Update(StageOBJ* stageObj);
	/// <summary>
	/// ���I�u�W�F�N�g�S�̂̍X�V
	/// </summary>
	void AllUpdate();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
	/// <summary>
	/// ���쐬
	/// </summary>
	/// <param name="position">�ʒu</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="angle">�p�x</param>
	/// <param name="map">�X�e�[�W�ʒu</param>
	/// <param name="type">���</param>
	/// <returns></returns>
	static StageOBJ SetDangerFish(const Vec3 &position, const Vec3& scale, const Vec3 &angle, const int type);
public:
	Vec3 GetFishAngle() { return m_rotation; }
private:
	ObjectData m_dangerFishOBJ;						//��OBJ
	bool m_dangerFishFlag = false;					//�����o�Ă��邩�ǂ���
	const int c_dangerFishTimeMax = 160;			//�댯�����ł�܂ł̍ő厞�Ԏ���
	int m_dangerFishTime = 0;						//�댯�����ł�܂ł̎���
	const Vec3 c_rotationFirst = { 0.0f,180.0f,0.0f };	//�����p�x
	Vec3 m_rotation = { 0.0f,180.0f,0.0f };			//���̊p�x
	//��ԏ�̂Ƃ�
	Vec3 m_start_end = { -50.0f,65.0f,0.0f };
	const float c_start_endTimeMax = 50.0f;
	float m_start_endTime = 0.0f;
	//��ԉ��̎�
	Vec3 m_end_end = { -100.0f,-40.0f,0.0f };
	const float c_end_endTimeMax = 50.0f;
	float m_end_endTime = 0.0f;
	//�댯���̃T�C�Y
	const Vec3 c_fishSize = { 12.5f,12.5f,12.5f };
};