#include "Particle.h"
#include <Safe_delete.h>
#include"Player.h"
#include"Stage.h"
Particle::Particle()
{
}

Particle::~Particle()
{
	safe_delete(breakBoxParticle);
}

void Particle::Init()
{
	graph = Texture::Get()->LoadTexture(L"Resources/particle.jpg");
	breakBoxParticle = ParticleManager::Create();
}

void Particle::Update()
{
	//箱が壊れるパーティクル
	if (breakBoxFlag == true)
	{
		breakBoxParticle->BreakBoxAdd(breakPos,0.5f, 5.0f, 5.0f,
			Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec4(0.0f, 0.0f, 0.0f, 0.0f));
		breakBoxFlag = false;
	}

	//パーティクル更新
	breakBoxParticle->Update();
}

void Particle::Draw()
{
	breakBoxParticle->Draw(graph);
}
