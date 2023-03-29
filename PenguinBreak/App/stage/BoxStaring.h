#pragma once
#include"ParticleManager.h"
#include"Particle3D.h"
#include<memory>
/// <summary>
/// �����o
/// </summary>
class BoxStaring
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BoxStaring();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~BoxStaring();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �QD�`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �RD�`��
	/// </summary>
	void Draw3D();

	void BreakBoxFlag(const Vec3& breakPos);

	void BombBoxFlag(const Vec3& bombPos);
private:
	/// <summary>
	/// ��ꂽ���̃p�[�e�B�N���쐬
	/// </summary>
	void CreateBreakBox();
	/// <summary>
	/// ���e���̃p�[�e�B�N���쐬
	/// </summary>
	void CreateBomb();
private:
	//2D
	//��������p�[�e�B�N��
	std::unique_ptr<ParticleManager>particle2D;
	Vec3 m_breakPos = {};
	int m_graph = 0;
	bool m_breakBoxFlag = false;
	//���e���͉���p�[�e�B�N��
	Vec3 m_bombPos = {};
	bool m_bombFlag = false;
	const int c_bombTimeMax = 10;
	int m_bombTime = 0;
	//3D
	//��ꂽ������юU��
	std::unique_ptr<Particle3D>particle3D;
	ObjectData m_boxData;
	int m_boxGraph = 0;
};

