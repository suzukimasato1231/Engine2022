#pragma once
#include"ParticleManager.h"
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

	void BreakBoxFlag(Vec3 breakPos) { breakBoxFlag = true; this->breakPos = breakPos; }
private:
	//箱が壊れるパーティクル
	ParticleManager* breakBoxParticle = nullptr;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
};

