#include "Staging.h"
#include"Safe_delete.h"
#include"Texture.h"
Staging::Staging()
{
}

Staging::~Staging()
{
	safe_delete(particle);
	safe_delete(electDie);
}

void Staging::Init()
{
	particle = ParticleManager::Create();
	electDie = ParticleManager::Create();
}

void Staging::Update()
{

	particle->Update();
	electDie->Update();
}

void Staging::Draw()
{
	particle->Draw(graph);
	electDie->Draw(graph);
}

void Staging::CreateElect(Vec3 pPos)
{
	static const int particleTime = 15;
	static const Vec3 velocity = { 0.0f,0.0f,0.0f };
	static const Vec3 accel = { 0.0f,0.0f,0.0f };
	static const float start_scale = 20.0f;
	static const float end_scale = 5.0f;
	static const Vec4 start_color = { 0.2f,0.2f,0.1f,0.5f };
	static const Vec4 end_color = { 0.2f,0.2f,0.1f,1.0f };
	for (int i = 0; i < 5; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 5.0f;
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 5.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		particle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}

void Staging::CreateFallDown(Vec3 pPos)
{
	static const int particleTime = 15;
	static const Vec3 velocity = { 0.0f,5.0f,0.0f };
	static const Vec3 accel = { 0.0f,0.01f,0.0f };
	static const float start_scale = 3.0f;
	static const float end_scale = 3.0f;
	static const Vec4 start_color = { 1.0f,1.0f,0.0f,1.0f };
	static const Vec4 end_color = {};
	for (int i = 0; i < 20; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 5.0f;
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 4.0f;
		particle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}
