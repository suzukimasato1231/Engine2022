#pragma once
#include"ParticleManager.h"
#include"Particle3D.h"
#include<memory>
class BoxStaring
{
public:
	BoxStaring();
	~BoxStaring();

	void Init();

	void Update();

	void Draw();

	void Draw3D();

	void BreakBoxFlag(Vec3 breakPos) { breakBoxFlag = true; this->breakPos = breakPos; }
private:
	//箱が壊れるパーティクル
	std::unique_ptr<ParticleManager>breakBoxParticle;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
	//壊れた箱が飛び散る
	std::unique_ptr<Particle3D>break3DParticle;
	ObjectData boxData;
	int boxGraph = 0;
};

