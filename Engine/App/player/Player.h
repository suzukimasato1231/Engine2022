#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"FBXObject3d.h"
#include"Staging.h"
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
private:
	enum PlayerFBX
	{
		None,
		Walk,

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
	FBXObject3d* fbxObject1[2] = {};
	//��~FBX
	Model* stopModel = nullptr;
	FBXObject3d* stopFbx[2] = {};

	int dieType = DIENULL;

	//�v���C���[���o
	Staging staging;
	int dieNowTime = 0;

	const int walkTimeMax = 5;
	int walkTime = walkTimeMax;

};