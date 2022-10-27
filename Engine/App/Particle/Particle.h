#pragma once
#include"ParticleManager.h"
#include"Particle3D.h"
#include "Safe_delete.h"
#include"Singleton.h"
class Particle :public Singleton<Particle>
{
private:
	friend Singleton<Particle>;
public:
	Particle();
	~Particle();

	void Init();

	void Update();

	void Draw();

	void Draw3D();

	void BreakBoxFlag(Vec3 breakPos) { breakBoxFlag = true; this->breakPos = breakPos; }
private:
	//��������p�[�e�B�N��
	ParticleManager* breakBoxParticle = nullptr;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
	//��ꂽ������юU��
	Particle3D* break3DParticle = nullptr;
	ObjectData boxData;
	int boxGraph = 0;
};

