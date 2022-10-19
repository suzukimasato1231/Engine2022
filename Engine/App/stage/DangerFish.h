#pragma once
#include"../stage/StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//����������
	void Init();
	//�X�V����
	void Update(StageOBJ* stageObj);
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
	//���̊p�x
	Vec3 rotation = { 0.0f,180.0f,0.0f };
	//��ԏ�̂Ƃ�
	Vec3 start_end = { -50.0f,65.0f,0.0f };
	const float start_endTimeMax = 100.0f;
	float start_endTime = 0.0f;
	//��ԉ��̎�
	Vec3 end_end = { -100.0f,-40.0f,0.0f };
	const float end_endTimeMax = 100.0f;
	float end_endTime = 0.0f;
	//�댯���̃T�C�Y
	const Vec3 fishSize = { 12.5f,12.5f,12.5f };
};