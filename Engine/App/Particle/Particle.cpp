#include "Particle.h"
#include"../Engine/App/player/Player.h"
#include"../Engine/App/stage/Stage.h"
#include"Shape.h"
Particle::Particle()
{}

Particle::~Particle()
{}

void Particle::Init()
{
	graph = Texture::Get()->LoadTexture(L"Resources/Paricle/particle.jpg");
	breakBoxParticle = std::make_unique<ParticleManager > ();
	breakBoxParticle->Initialize();

	break3DParticle = std::make_unique<Particle3D>();
	boxData = Shape::CreateSquare(2.0f, 2.0f, 1.0f);
	boxGraph = Texture::Get()->LoadTexture(L"Resources/Paricle/boxParticle.png");
}

void Particle::Update()
{
	//��������p�[�e�B�N��
	if (breakBoxFlag == true)
	{
		breakBoxParticle->BreakBoxAdd(breakPos,0.5f, 5.0f, 5.0f,
			Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec4(0.0f, 0.0f, 0.0f, 0.0f));
		breakBoxFlag = false;

		static const int particleTime = 35;
		static const Vec3 Velocity = { 0.0f,0.0f,0.0f };
		static const Vec3 accel = { 0.0f,-0.2f,0.0f };
		for (int i = 0; i < 5; i++)
		{
			//X,Y,Z�S��{-5.0f,+5.0f}�Ń����_���ɕ��z
			const float md_pos = 1.0f;
			Vec3 pos = breakPos;
			pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.y += 0.0f;
			pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			const float md_vec = 4.0f;
			Vec3 velocity = Velocity;
			velocity.x += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
			velocity.y += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
			velocity.z += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
			break3DParticle->Create(pos, velocity, accel, particleTime);
		}
	}

	//�p�[�e�B�N���X�V
	breakBoxParticle->Update();

	break3DParticle->Update();
}

void Particle::Draw()
{
	breakBoxParticle->Draw(graph);
}

void Particle::Draw3D()
{
	break3DParticle->Draw(boxData,boxGraph);
}

