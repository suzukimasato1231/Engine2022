#pragma once
#include"StegeObject.h"
class DangerFish
{

public:
	DangerFish();

	~DangerFish();
	//����������
	void Init();
	//�X�V����
	void Update(StageOBJ* stageObj);

	void AllUpdate();
	//�`�揈��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
public:
	Vec3 GetFishAngle() { return m_rotation; }

private:
	ObjectData m_dangerFishOBJ;
	//�����o�Ă��邩�ǂ���
	bool m_dangerFishFlag = false;
	//�댯�����ł�܂ł̍ő厞�Ԏ���
	const int c_dangerFishTimeMax = 160;
	//�댯�����ł�܂ł̎���
	int m_dangerFishTime = 0;
	//���̊p�x
	Vec3 m_rotation = { 0.0f,180.0f,0.0f };
	//��ԏ�̂Ƃ�
	Vec3 m_start_end = { -50.0f,65.0f,0.0f };
	const float c_start_endTimeMax = 50.0f;
	float m_start_endTime = 0.0f;
	//��ԉ��̎�
	Vec3 m_end_end = { -100.0f,-40.0f,0.0f };
	const float c_end_endTimeMax = 50.0f;
	float m_end_endTime = 0.0f;
	//�댯���̃T�C�Y
	const Vec3 c_fishSize = { 12.5f,12.5f,12.5f };
};