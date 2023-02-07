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

	startObject = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	startParicle = Particle3D::Create();
	start_color[0] = Texture::Get()->LoadTexture(L"Resources/Paricle/startWhite.png");
	start_color[1] = Texture::Get()->LoadTexture(L"Resources/Paricle/starBlack.png");
	start_color[2] = Texture::Get()->LoadTexture(L"Resources/Paricle/startYellow.png");
}

void Staging::Update()
{
	electDie->Update();
	walk->Update();
	fallParicle->Update();
	startParicle->Update();
}

void Staging::Draw()
{
	electDie->Draw(graph);
	walk->Draw(graph);
}

void Staging::Draw3D()
{
	fallParicle->Draw(fallDown);
	startParicle->Draw(startObject);
}

void Staging::CreateElect(const Vec3 &pPos)
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

void Staging::CreateWalk(const Vec3 &pPos, const Vec3 &vec)
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

void Staging::CreateFallDown(const Vec3 &pPos)
{
	static const int particleTime = 35;
	static const Vec3 Velocity = { 0.0f,5.0f,0.0f };
	static const Vec3 accel = { 0.0f,-0.2f,0.0f };

	const float md_pos = 1.0f;
	Vec3 pos = pPos;
	const float md_vec = 3.0f;
	Vec3 velocity = Velocity;
	for (int i = 0; i < 5; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 0.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		velocity.x += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.y += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.z += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		fallParicle->Create(pos, velocity, accel, particleTime);
	}
}

void Staging::CreateStart(const Vec3 &pPos)
{
	static const int particleTime = 30;
	static const Vec3 accel = { 0.0f,0.0f,0.0f };
	Vec3 m_pos = pPos + Vec3(0.0f, 3.0f, 0.0f);
	for (int i = 0; i < 30; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 30.0f;
		Vec3 pos = m_pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		Vec3 md_vec = m_pos - pos;
		Vec3 velocity = {};
		velocity.x += md_vec.x / particleTime;
		velocity.y += md_vec.y / particleTime;
		velocity.z += md_vec.z / particleTime;

		int graph_num = rand() % 3;

		if (graph_num == 0) { graph_num = start_color[0]; }
		else if (graph_num == 1) { graph_num = start_color[1]; }
		else { graph_num = start_color[2]; }
		startParicle->Create(pos, velocity, accel, particleTime, graph_num);
	}
}
