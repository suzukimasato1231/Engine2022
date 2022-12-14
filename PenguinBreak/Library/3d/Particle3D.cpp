#include "Particle3D.h"

Particle3D::Particle3D()
{
}

Particle3D::~Particle3D()
{
	for (int i = (int)particle.size() - 1; i >= 0; i--)
	{
		delete particle[i];
		particle.erase(particle.begin() + i);
	}
}

void Particle3D::Init()
{}

void Particle3D::Update()
{
	for (size_t i = 0; i < particle.size(); i++)
	{
		//フレーム更新
		particle[i]->framNow++;
		//速度を足す
		particle[i]->position += particle[i]->velocity;
		particle[i]->velocity += particle[i]->accel;
		float f = (float)particle[i]->framNow / particle[i]->framMax;
		if (f >= 1.0f)
		{
			delete particle[i];
			particle.erase(particle.begin() + i);
		}
	}
}

void Particle3D::Draw(ObjectData objectData,int graph)
{
	for (size_t i = 0; i < particle.size(); i++)
	{
		Object::NoShadowDraw(objectData, particle[i]->psr,
			particle[i]->position, Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f),Vec2(),graph);
	}
}

void Particle3D::Create(Vec3 pos, Vec3 velocity, Vec3 accel, int time)
{
	particle.push_back(new ParticleData);
	size_t num = particle.size() - 1;
	particle[num]->position = pos;
	particle[num]->velocity = velocity;
	particle[num]->accel = accel;
	particle[num]->framMax = time;
}

Particle3D* Particle3D::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Particle3D* particle = new Particle3D();
	return particle;
}
