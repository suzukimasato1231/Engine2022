#pragma once
#include <Object.h>
//3Dパーティクル
class Particle3D
{
private:
	struct ParticleData
	{
		PSR psr = {};
		Vec3 position = {};
		Vec3 velocity = {};
		Vec3 accel = {};
		int framNow = 0;
		int framMax;
	};
public:
	//コンストラクタ
	Particle3D();
	//デスコンストラクタ
	~Particle3D();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(ObjectData objectData, int graph = 0);
	//作成
	void Create(Vec3 pos, Vec3 velocity, Vec3 accel, int time);

	static Particle3D* Create();
private:
	std::vector<ParticleData*>particle;
};


