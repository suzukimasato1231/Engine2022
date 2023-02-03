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
		int graph = 0;
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
	void Draw(const ObjectData &objectData, int graph = 0);
	//�쐬
	void Create(const Vec3 &pos,const  Vec3 &velocity,const  Vec3 &accel,const  int &time,const int &graph = 0);

	static Particle3D* Create();
private:
	std::vector<ParticleData*>particle;
};


