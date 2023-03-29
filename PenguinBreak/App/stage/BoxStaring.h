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
	/// ２D描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ３D描画
	/// </summary>
	void Draw3D();

	void BreakBoxFlag(const Vec3& breakPos);

	void BombBoxFlag(const Vec3& bombPos);
private:
	/// <summary>
	/// 壊れた箱のパーティクル作成
	/// </summary>
	void CreateBreakBox();
	/// <summary>
	/// 爆弾箱のパーティクル作成
	/// </summary>
	void CreateBomb();
private:
	//2D
	//箱が壊れるパーティクル
	std::unique_ptr<ParticleManager>particle2D;
	Vec3 m_breakPos = {};
	int m_graph = 0;
	bool m_breakBoxFlag = false;
	//爆弾箱は壊れるパーティクル
	Vec3 m_bombPos = {};
	bool m_bombFlag = false;
	const int c_bombTimeMax = 10;
	int m_bombTime = 0;
	//3D
	//壊れた箱が飛び散る
	std::unique_ptr<Particle3D>particle3D;
	ObjectData m_boxData;
	int m_boxGraph = 0;
};

