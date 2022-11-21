#pragma once
#include"Vec.h"
#include <CollisionPrimitive.h>
#include"Object.h"
enum StageFloor
{
	NoneFloor,
	FloorNormal,	//���ʂ̏�
	Floor169,		//�΂ߏ�
	Floor11,		//�΂ߏ�
	FloorMove,		//�ړ���
	FloorPitfall_A,	//���Ƃ���A
	FloorPitfall_B,	//���Ƃ���B
};

enum StageType
{
	NoneOBJ = 0,
	Wall = 1,			//��
	Goal = 2,			//�S�[��
	BOX = 10,			//���锠
	BOXDOUBLE = 11,		//���锠�_�u��
	BOXHARD = 12,		//�ł���
	BOXJUMP = 13,		//�W�����v��
	ICICLE = 20,		//�X��
	ELECTRICITY = 21,	//�d�C
	FISHATTACK  = 22,	//���A�^�b�N
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
	int type = NoneOBJ;
	Vec3 actionPos = {};
};