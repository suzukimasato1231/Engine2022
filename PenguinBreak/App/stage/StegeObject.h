#pragma once
#include"Vec.h"
#include <CollisionPrimitive.h>
#include"Object.h"
enum StageFloor
{
	NONEFLOOR,
	FLOORNORMAL,	//���ʂ̏�
	FLOOR169,		//�΂ߏ�
	FLOOR11,		//�΂ߏ�
	FLOORMOVE,		//�ړ���
	FLOORPITFALL_A,	//���Ƃ���A
	FLOORPITFALL_B,	//���Ƃ���B
	FLOORMOVE2,		//�ړ���
};

enum StageType
{
	NONEOBJ = 0,
	WALL = 1,			//��
	GOAL = 2,			//�S�[��
	BARRIERWALL = 3,	//�o���A�u���b�N
	BOX = 10,			//���锠
	BOXDOUBLE = 11,		//���锠�_�u��
	BOXHARD = 12,		//�ł���
	BOXJUMP = 13,		//�W�����v��
	BOXBOMB = 14,		//���e��
	BOX_BOMB = 15,		//���锠�̏�ɔ��e��
	BOMB_BOX = 16,		//���e���̏�ɉ��锠
	ICICLE = 20,		//�X��
	ELECTRICITY = 21,	//�d�C
	FISHATTACK = 22,	//���A�^�b�N
	DEADTREE = 30,		//�͂��
	STLON = 31,			//��
	ICEARCH = 32,		//�X�̃A�[�`
	SIGNBOARD1 = 40,	//�ŔW�����v
	SIGNBOARD2 = 41,	//�ŔX�s��
};
struct Floor
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	int type = 0;
	int time = 0;
	int moveFlag = 0;
	Vec3 speed = { 0.0f,0.0f,0.5f };
	Vec3 drawAngle = {};
	int size = 0;
};

struct FloorPitfallData
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec3 drawAngle = {};//�`��p
	Vec2 map = {};
	int time = 0;
	int moveFlag = 0;
};

struct StageOBJ
{
	PSR psr = {};
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 angle = {};
	Vec2 map = {};
	Box box = {};
	int type = NONEOBJ;
	Vec3 actionPos = {};
};