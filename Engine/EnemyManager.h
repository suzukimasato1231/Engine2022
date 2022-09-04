#pragma once
#include"Vec.h"
#include"Enemy.h"
#include "StegeObject.h"
//�G�l�~�[�}�l�W���[
class EnemyManager
{
protected:

public:
	EnemyManager();

	~EnemyManager();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(bool shadowFlag = false);

	void FloorPush(Floor floor);
private:
	std::vector<Enemy*>enemy;

	ObjectData enemyData;
};

