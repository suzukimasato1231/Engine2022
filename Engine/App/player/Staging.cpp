#include "Staging.h"
#include"Safe_delete.h"
#include"Texture.h"
#include"Shape.h"
Staging::Staging()
{}
Staging::~Staging()
{
	safe_delete(electDie);
	safe_delete(walk);
	safe_delete(fallParicle);
}

void Staging::Init()
{
	electDie = ParticleManager::Create();
	walk = ParticleManager::Create();
	fallParicle = Particle3D::Create();
	fallDown = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
}

void Staging::Update()
{
	electDie->Update();
	walk->Update();
	fallParicle->Update();
}

void Staging::Draw()
{
	electDie->Draw(graph);
	walk->Draw(graph);
}

void Staging::Draw3D()
{
	fallParicle->Draw(fallDown);
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
		electDie->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}

void Staging::CreateWalk(Vec3 pPos, Vec3 vec)
{
	static const int particleTime = 15;
	static const Vec3 accel = { 0.0f,0.0f,0.0f };
	static const float start_scale = 3.0f;
	static const float end_scale = 0.0f;
	static const Vec4 start_color = { 0.3f,0.3f,0.3f,0.3f };
	static const Vec4 end_color = { 0.0f,0.0f,0.0f,0.0f };
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 1.0f;
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 0.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		walk->Add(particleTime, pos, -vec, accel, start_scale, end_scale, start_color, end_color);
	}
}

void Staging::CreateFallDown(Vec3 pPos)
{
	static const int particleTime = 35;
	static const Vec3 Velocity = { 0.0f,5.0f,0.0f };
	static const Vec3 accel = { 0.0f,-0.2f,0.0f };
	for (int i = 0; i < 5; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 1.0f;
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 0.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		const float md_vec = 3.0f;
		Vec3 velocity = Velocity;
		velocity.x += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.y += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.z += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		fallParicle->Create(pos, velocity, accel, particleTime);
	}
}