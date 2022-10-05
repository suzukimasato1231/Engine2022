#include "PlayerFallDie.h"
#include"Safe_delete.h"
#include"Texture.h"
PlayerFallDie::PlayerFallDie()
{
}

PlayerFallDie::~PlayerFallDie()
{
	safe_delete(particle);
}

void PlayerFallDie::Init()
{
	particle = ParticleManager::Create();
}

void PlayerFallDie::Update()
{

	particle->Update();
}

void PlayerFallDie::Draw()
{
	particle->Draw(graph);
}

void PlayerFallDie::Create(Vec3 pPos)
{
	static const int particleTime = 15;
	static const Vec3 velocity = { 0.0f,5.0f,0.0f };
	static const Vec3 accel = { 0.0f,0.01f,0.0f };
	static const float start_scale = 3.0f;
	static const float end_scale = 3.0f;
	static const Vec4 start_color = { 1.0f,1.0f,1.0f,1.0f };
	static const Vec4 end_color = {};
	for (int i = 0; i < 20; i++)
	{
		//X,Y,Z‘S‚Ä{-5.0f,+5.0f}‚Åƒ‰ƒ“ƒ_ƒ€‚É•ª•z
		const float md_pos = 5.0f;
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 4.0f;
		particle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}
