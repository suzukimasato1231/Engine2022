#include "BoxStaring.h"
#include"../player/Player.h"
#include"Stage.h"
#include"Shape.h"
BoxStaring::BoxStaring()
{}

BoxStaring::~BoxStaring()
{}

void BoxStaring::Init()
{
	m_graph = Texture::Get()->LoadTexture(L"Resources/Paricle/particle.jpg");
	m_breakBoxParticle = std::make_unique<ParticleManager > ();
	m_breakBoxParticle->Initialize();

	m_bombParticle = std::make_unique<ParticleManager >();
	m_bombParticle->Initialize();

	m_break3DParticle = std::make_unique<Particle3D>();
	m_boxData = Shape::CreateSquare(2.0f, 2.0f, 1.0f);
	m_boxGraph = Texture::Get()->LoadTexture(L"Resources/Paricle/boxParticle.png");
}

void BoxStaring::Update()
{
	
	CreateBreakBox();

	CreateBomb();

	//パーティクル更新
	m_breakBoxParticle->Update();

	m_bombParticle->Update();

	m_break3DParticle->Update();
}

void BoxStaring::Draw()
{
	m_breakBoxParticle->Draw(m_graph);
	m_bombParticle->Draw(m_graph);
}

void BoxStaring::Draw3D()
{
	m_break3DParticle->Draw(m_boxData, m_boxGraph);
}

void BoxStaring::BreakBoxFlag(const Vec3& breakPos)
{
	m_breakBoxFlag = true;
	m_breakPos = breakPos;
}

void BoxStaring::BombBoxFlag(const Vec3& bombPos)
{
	m_bombFlag = true;
	m_bombPos = bombPos;
}

void BoxStaring::CreateBreakBox()
{
	//箱が壊れるパーティクル
	if (m_breakBoxFlag == true)
	{
		m_breakBoxParticle->BreakBoxAdd(m_breakPos, 0.5f, 5.0f, 5.0f,
			Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec4(0.0f, 0.0f, 0.0f, 0.0f));
		m_breakBoxFlag = false;

		static const int particleTime = 55;
		static const Vec3 Velocity = { 0.0f,0.0f,0.0f };
		static const Vec3 accel = { 0.0f,-0.2f,0.0f };
		static const Vec3 anglePlas = {2.0f,2.0f,2.0f};
		static const Vec3 scale = { 3.0f,3.0f,3.0f };
		for (int i = 0; i < 15; i++)
		{
			//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
			const float md_pos = 1.0f;
			Vec3 pos = m_breakPos;
			pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			const float md_vec = 7.0f;
			Vec3 velocity = Velocity;
			velocity.x += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
			velocity.y += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
			velocity.z += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;

			m_break3DParticle->Create(pos, velocity, accel,anglePlas, particleTime);
		}
	}
}

void BoxStaring::CreateBomb()
{
	//箱が壊れるパーティクル
	if (m_bombFlag == true)
	{
		m_bombTime++;

		m_bombParticle->BombAdd(m_bombPos, 1.8f, 5.0f, 3.0f,
			Vec4(1.0f, 1.0f, 0.3f, 1.0f), Vec4(0.5f, 0.0f, 0.0f, 1.0f));
		if (m_bombTime <= c_bombTimeMax)
		{
			m_bombFlag = false;
			m_bombTime = 0;
		}
	}
}

