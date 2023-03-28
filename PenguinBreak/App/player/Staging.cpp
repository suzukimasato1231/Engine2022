#include "Staging.h"
#include"Texture.h"
#include"Shape.h"
Staging::Staging()
{}
Staging::~Staging()
{}

void Staging::Init()
{
	m_electDie = std::make_unique<ParticleManager>();
	m_electDie->Initialize();
	m_walk = std::make_unique<ParticleManager>();
	m_walk->Initialize();
	m_fallParicle = std::make_unique <Particle3D>();
	m_startParicle = std::make_unique <Particle3D>();

	m_fallDown = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	m_startObject = Shape::CreateSquare(1.0f, 1.0f, 1.0f);

	m_start_color[0] = Texture::Get()->LoadTexture(L"Resources/Paricle/startWhite.png");
	m_start_color[1] = Texture::Get()->LoadTexture(L"Resources/Paricle/starBlack.png");
	m_start_color[2] = Texture::Get()->LoadTexture(L"Resources/Paricle/startYellow.png");
}

void Staging::Update()
{
	m_electDie->Update();
	m_walk->Update();
	m_fallParicle->Update();
	m_startParicle->Update();
}

void Staging::Draw()
{
	m_electDie->Draw(m_graph);
	m_walk->Draw(m_graph);
}

void Staging::Draw3D()
{
	m_fallParicle->Draw(m_fallDown);
	m_startParicle->Draw(m_startObject);
}

void Staging::CreateElect(const Vec3 pPos)
{
	//電気パーティクル
	const int c_electTime = 15;                             //パーティクルが出てる時間
	const Vec3 c_electVel = { 0.0f,0.0f,0.0f };			    //進む速度
	const Vec3 c_electAccel = { 0.0f,0.0f,0.0f };           //加速度
	const float c_electStart_scale = 20.0f;
	const float c_electEnd_scale = 5.0f;
	const Vec4 c_electStart_color = { 0.2f,0.2f,0.1f,0.5f };
	const Vec4 c_electEnd_color = { 0.2f,0.2f,0.1f,1.0f };
	//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
	const float md_pos = 5.0f;
	for (int i = 0; i < 5; i++)
	{
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 5.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		m_electDie->Add(c_electTime, pos, c_electVel, c_electAccel, c_electStart_scale, c_electEnd_scale, c_electStart_color, c_electEnd_color);
	}
}

void Staging::CreateWalk(const Vec3& pPos, const Vec3& vec)
{
	const int particleTime = 15;
	const Vec3 accel = { 0.0f,0.0f,0.0f };
	const float start_scale = 3.0f;
	const float end_scale = 0.0f;
	const Vec4 start_color = { 0.3f,0.3f,0.3f,0.3f };
	const Vec4 end_color = { 0.0f,0.0f,0.0f,0.0f };
	//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
	const float md_pos = 1.0f;
	for (int i = 0; i < 1; i++)
	{
		Vec3 pos = pPos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += 0.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		m_walk->Add(particleTime, pos, -vec, accel, start_scale, end_scale, start_color, end_color);
	}
}

void Staging::CreateFallDown(const Vec3& pPos)
{
	const int particleTime = 35;
	const Vec3 accel = { 0.0f,-0.2f,0.0f };
	const float md_pos = 1.0f;
	Vec3 pos = pPos;
	const float md_vec = 6.0f;
	Vec3 velocity = { 0.0f,5.0f,0.0f };
	const Vec3 anglePlas = {};
	for (int i = 0; i < 5; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		velocity.x += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.y += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		velocity.z += (float)rand() / RAND_MAX * md_vec - md_vec / 2.0f;
		m_fallParicle->Create(pos, velocity, accel,anglePlas, particleTime);
	}
}

void Staging::CreateStart(const Vec3& pPos)
{
	const int particleTime = 30;
	const Vec3 accel = {};
	Vec3 m_pos = pPos + Vec3(0.0f, 3.0f, 0.0f);
	const Vec3 anglePlas = {};
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

		if (graph_num == 0) { graph_num = m_start_color[0]; }
		else if (graph_num == 1) { graph_num = m_start_color[1]; }
		else { graph_num = m_start_color[2]; }
		m_startParicle->Create(pos, velocity, accel,anglePlas, particleTime, graph_num);
	}
}
