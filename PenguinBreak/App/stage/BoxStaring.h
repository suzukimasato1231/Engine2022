#pragma once
#include"ParticleManager.h"
#include"Particle3D.h"
#include<memory>
/// <summary>
/// 箱演出
/// </summary>
class BoxStaring
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BoxStaring();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~BoxStaring();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Draw3D();

	void BreakBoxFlag(const Vec3 &breakPos) { breakBoxFlag = true; this->breakPos = breakPos; }
private:
	//箱が壊れるパーティクル
	std::unique_ptr<ParticleManager>breakBoxParticle;
	Vec3 breakPos = {};
	int graph = 0;
	bool breakBoxFlag = false;
	//壊れた箱が飛び散る
	std::unique_ptr<Particle3D>break3DParticle;
	ObjectData boxData;
	int boxGraph = 0;
};

