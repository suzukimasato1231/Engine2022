#pragma once
#include <Object.h>
//3D�p�[�e�B�N��
class Particle3D
{
private:
	struct ParticleData
	{
		PSR psr = {};
		Vec3 position = {};
		Vec3 velocity = {};
		Vec3 accel = {};
		int framNow = 0;
		int framMax;
	};
public:
	//�R���X�g���N�^
	Particle3D();
	//�f�X�R���X�g���N�^
	~Particle3D();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(ObjectData objectData, int graph = 0);
	//�쐬
	void Create(Vec3 pos, Vec3 velocity, Vec3 accel, int time);

	static Particle3D* Create();
private:
	std::vector<ParticleData*>particle;
};


