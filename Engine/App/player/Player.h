#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"FBXObject3d.h"
#include"Staging.h"
#include<memory>
enum DieType
{
	DIENULL,
	FALLDOWN,
	ELECTDIE,
	EATDIE,
	DIENOW,
};
class Player :public Singleton<Player>
{
public:
	friend Singleton<Player>;
public:
	Player();		//�R���X�g���N�^

	~Player();		//�f�X�R���X�g���N�^

	void Init();	//������

	void Update();						//�X�V

	void Draw(bool shadowFlag = false);//�`��

	void DrawParticle();//�v���C���[�����񂾂Ƃ��̃p�[�e�B�N��

	void SetPosition(Vec3 position);

	/// <summary>
	/// true�ɂ���
	/// </summary>
	void GroundFlag();

	void Reset();

	void GetBlockStepOnFlag() { blockStepOnFlag = true; }

	void JumpPoweZero() { jumpPower = 0; }

	//2D false 3D true
	void ChangeMoveFlag(bool moveFlag) { Player::moveFlag = moveFlag; }

	void GetJumpBox() { jumpBoxFlag = true; }
	//�����󂵂���
	void ChangeBreakFlag() { changeBreakFlag = true; }

	void DieType(int type) { if (dieType != DIENOW) { Player::dieType = type; } }

	void Delete();

	void FishDie(Vec3 pos, Vec3 angle) { fishDiePos = pos, this->fishDieAngle, angle; }
private:
	enum PlayerFBX
	{
		None,
		Walk,
		ElectDie,
	};
private:
	/// <summary>
	/// FBX�̕`��
	/// </summary>
	void FbxDraw(bool shadowFlag);
	/// <summary>
	/// �v���C���[�ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// �v���C���[�W�����v
	/// </summary>
	void Jump();

	//�����Ď��S�����Ƃ�
	void FallDie();

	void Fish();

	void RedFishDie();
public://�擾�n
	//���W
	Vec3 GetPosition() { return position; }

	Vec3 GetOldPosition() { return oldPosition; }

	Vec3 GetPSize() { return pScale; }

	Box GetBox() { return pBox; }

	Vec3 GetVec() { return vec; }

	float GetJumpPower() { return jumpPower; }

	bool GetGroundFlag() { return groundFlag; }

	bool GetOldGroundFlag() { return oldGroundFlag; }
	//�c�@���l��
	int GetRemanLives() { return remainLives; }

	int GetFishNum() { return fishNum; }

	bool GetGameoverFlag() { return gameoverFlag; }

	bool GetIsFishDie() { return isFishDie; }
private:
	//2D false 3D true
	bool moveFlag = false;

	bool gameoverFlag = false;

	ObjectData playerObject;			//�v���C���[�I�u�W�F�N�g
	PSR psr = {};
	Vec3 position{ 64.0f,14.0f,80.0f };	//���W
	Vec3 oldPosition{};					//1�O�̍��W
	Vec3 speed{ 2.0f,2.0f,2.0f };		//�v���C���[�X�s�[�h
	Vec3 scale{ 2.5f,2.5f,2.5f };		//�傫��
	Vec3 angle{ -30.0f,180.0f,0.0f };	//�p�x
	Vec3 pScale = { 8.0f,7.0f,10.0f };	//�v���C���[�傫��
	Sphere pSphere;						//�v���C���[�̋�
	Box pBox;							//�v���C���[�̔�
	Vec3 vec = {};

	bool changeBreakFlag = false;

	const int remainLivesMax = 3;		//�P�X�e�[�W�̎c�@��
	int remainLives = 3;				//�c�@

	//�W�����v
	const float jumpPowerMax = 8.0f;
	const float jumpBoxPowerMax = 9.0f;	//�W�����v��̃W�����v�p���[
	bool jumpBoxFlag = false;
	float jumpPower = 8.0f;				//�W�����v�p���[
	float jumpPowerDelay = 0.2f;
	float gravity = 5.0f;				//�d��
	bool groundFlag = false;			//�n�ʂɐڂ��Ă��邩�ǂ���
	bool oldGroundFlag = false;			//�n�ʂɐڂ��Ă������ǂ���
	bool blockStepOnFlag = false;		//�u���b�N�𓥂�ŉ󂵂����ǂ���

	//��
	bool fishFlag = false;
	int fishNum = 0;

	//FBX
	int fbxType = NULL;
	bool fbxFlag[2] = {};
	//����FBX
	Model* model1 = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject1[2];
	//��~FBX
	Model* stopModel = nullptr;
	std::unique_ptr<FBXObject3d> stopFbx[2];
	//���d
	Model* electModel = nullptr;
	std::unique_ptr<FBXObject3d> electFbx[2];

	int dieType = DIENULL;

	//�v���C���[���o
	Staging staging;
	int dieNowTime = 0;

	const int walkTimeMax = 5;
	int walkTime = walkTimeMax;

	//�����S���̏��
	Vec3 fishDiePos = {};
	Vec3 fishDieAngle = {};
	bool isFishDie = false;
};