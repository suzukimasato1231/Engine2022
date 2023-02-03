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
		int graph = 0;
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
	void Draw(const ObjectData &objectData, int graph = 0);
	//作成
	void Create(const Vec3 &pos,const  Vec3 &velocity,const  Vec3 &accel,const  int &time,const int &graph = 0);

	static Particle3D* Create();
private:
	std::vector<ParticleData*>particle;
};


