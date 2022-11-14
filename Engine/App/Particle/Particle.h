#pragma once
#include"ParticleManager.h"
#include"Particle3D.h"
#include "Safe_delete.h"
#include"Singleton.h"
#include<memory>
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
	std::unique_ptr<ParticleManager>breakBoxParticle;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
	//��ꂽ������юU��
	std::unique_ptr<Particle3D>break3DParticle;
	ObjectData boxData;
	int boxGraph = 0;
};

