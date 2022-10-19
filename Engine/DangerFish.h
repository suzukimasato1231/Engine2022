#pragma once
#include"../Engine/App/stage/StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
private:
	ObjectData dangerFishOBJ;
	//�����o�Ă��邩�ǂ���
	bool dangerFishFlag = false;
	//�댯�����ł�܂ł̍ő厞�Ԏ���
	const int dangerFishTimeMax = 150;
	//�댯�����ł�܂ł̎���
	int dangerFishTime = 0;
	//�����i�ގ���
	float speed = {};
	//���̊p�x
	Vec3 rotation = {};
};