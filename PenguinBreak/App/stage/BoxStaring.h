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
	/// �`��
	/// </summary>
	void Draw();

	void Draw3D();

	void BreakBoxFlag(const Vec3 &breakPos) { breakBoxFlag = true; this->breakPos = breakPos; }
private:
	//��������p�[�e�B�N��
	std::unique_ptr<ParticleManager>breakBoxParticle;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
	//��ꂽ������юU��
	std::unique_ptr<Particle3D>break3DParticle;
	ObjectData boxData;
	int boxGraph = 0;
};

