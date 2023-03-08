#pragma once
#include"StegeObject.h"
#include"ParticleManager.h"
#include<memory>
/// <summary>
/// �d�C���
/// </summary>
class Electricity
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Electricity();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~Electricity();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �S�̂̍X�V
	/// </summary>
	void AllUpdate();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="Z">Z���ʒu</param>
	void Update(StageOBJ* stageObj, const int Z);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
	/// <summary>
	/// �p�[�e�B�N���`��
	/// </summary>
	void DrawParicle();

	static StageOBJ SetElect(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, const int type);
private:
	//�d�C�p�[�e�B�N��
	void AddElect(Vec3 pos);
private:
	//�d�C���I�u�W�F�N�g
	ObjectData m_electOBJ;
	//�d�C�I�u�W�F�N�g
	ObjectData m_electShockOBJ;

	//�d�CON/OFF
	bool m_electFlag = false;
	//�d�C�؂�ւ��ő厞�Ԏ���
	const int c_electTimeMax = 150;
	//�؂�ւ��܂ł̎���
	int m_electTime = 0;
	//�d�C�т�т�
	std::unique_ptr<ParticleManager>m_electParicle = nullptr;
	int m_electParicleGraph = 0;

	Vec2 m_uvScroll = { 0.0f ,0.0f };
};

