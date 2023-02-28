#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"FBXObject3d.h"
#include"Staging.h"
#include<memory>
#include <Audio.h>
#include"PlayerFBX.h"
/// <summary>
/// ���S�^�C�v
/// </summary>
enum DieType
{
	DIENULL,
	FALLDOWN,
	ELECTDIE,
	EATDIE,
	BOMBDIE,
	DIENOW,
};

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player :public Singleton<Player>
{
public:
	friend Singleton<Player>;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	//�f�X�R���X�g���N�^
	~Player();
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
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(bool shadowFlag = false);
	/// <summary>
	/// �v���C���[����o��p�[�e�B�N���`��
	/// </summary>
	void DrawParticle();
	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	/// <param name="position">�ݒ肷����W</param>
	void SetPosition(const Vec3& position);
	/// <summary>
	/// �n�ʐڒntrue�ɂ���
	/// </summary>
	void ActivateGround() { groundFlag = true; }
	/// <summary>
	/// �l���Z�b�g
	/// </summary>
	void Reset();
	/// <summary>
	///�@�����W�����v�ŉ󂵂���
	/// </summary>
	void ActivateBlockStepOn() { blockStepOnFlag = true; }
	/// <summary>
	/// �W�����v�͂��[���ɂ���
	/// </summary>
	void JumpPoweZero() { jumpPower = 0; }
	/// <summary>
	/// 2D false 3D true�@
	/// </summary>
	/// <param name="moveFlag">2D��3D�̃t���O</param>
	void ChangeMoveFlag(bool moveFlag) { Player::moveFlag = moveFlag; }
	/// <summary>
	/// �W�����v���𓥂񂾂�
	/// </summary>
	void ActivateJumpBox() { jumpBoxFlag = true; }
	/// <summary>
	/// �����󂵂���
	/// </summary>
	void ActivateChangeBreak() { changeBreakFlag = true; }

	void DieType(int type) { if (dieType != DIENOW) { Player::dieType = type; } }

	void Delete();

	void FishDie(const Vec3& pos, const Vec3& angle) { fishDiePos = pos, this->fishDieAngle, angle; }
	//�S�[�����̉��o
	void GoalStaging(int fbxType);

	void GetClearFlag(bool clearFlag) { this->clearFlag = clearFlag; }

	int GetDecLifeFlag() { return decLifeTime; }

	void StopAnimation();
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
	/// <summary>
	/// ���̉��Z
	/// </summary>
	void Fish();
	/// <summary>
	/// �Ԃ����ɕ߂܂����Ƃ��̏���
	/// </summary>
	void RedFishDie();
	/// <summary>
	/// �X�s���U��
	/// </summary>
	void SpinAttack();
	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	void AnimationUpdate();
	/// <summary>
	/// ���̍X�V
	/// </summary>
	void AudioUpdate();
public://�擾�n
	inline Vec3 GetPosition() { return position; }

	inline Vec3 GetOldPosition() { return oldPosition; }

	inline Vec3 GetPSize() { return pScale; }

	inline Box GetBox() { return pBox; }

	inline Vec3 GetVec() { return vec; }

	inline float GetJumpPower() { return jumpPower; }

	inline bool GetGroundFlag() { return groundFlag; }

	inline bool GetOldGroundFlag() { return oldGroundFlag; }
	
	inline int GetRemanLives() { return remainLives; }

	inline int GetFishNum() { return fishNum; }

	inline bool GetGameoverFlag() { return gameoverFlag; }

	inline bool GetIsFishDie() { return isFishDie; }

	inline Box GetSpinBox() { return spinAttack; }

	inline bool GetSpinFlag() { return spinFlag; }
private:
	//�Q�[���t���O
	bool moveFlag = false;								//2D false 3D true
	bool gameoverFlag = false;							//�Q�[���I�[�o�[���ǂ���
	bool clearFlag = false;								//�N���A�������ǂ���
	//�v���C���[�X�e�[�^�X
	ObjectData playerObject;							//�v���C���[�I�u�W�F�N�g
	PSR psr = {};										//�v���C���[�̈ʒu���W�傫���ۑ��p
	Vec3 position = { 94.0f,14.0f,80.0f };				//���W
	const Vec3 firstPosition = { 90.0f,25.0f,80.0f };	//�����ʒu
	Vec3 oldPosition = {};								//1�O�̍��W
	const Vec3 speed = { 2.0f,2.0f,2.0f };				//����X�s�[�h
	const Vec3 walkSpeed = { 1.0f,1.0f,1.0f };			//�����X�s�[�h
	Vec3 angle = { -30.0f,180.0f,0.0f };				//�p�x
	const Vec3 firstAngle = { -30.0f,180.0f,0.0f };		//�ŏ��̊p�x
	Vec3 pScale = { 12.0f,5.0f,12.0f };					//�v���C���[�̑傫��
	Box pBox;											//�v���C���[BOX
	Vec3 vec = {};
	bool changeBreakFlag = false;

	const int remainLivesMax = 3;						//�P�X�e�[�W�̎c�@��
	int remainLives = 3;								//�c�@

	//�W�����v
	const float jumpPowerMax = 8.0f;					//�W�����v�p���[
	const float jumpBoxPowerMax = 9.0f;					//�W�����v��̃W�����v�p���[
	bool jumpBoxFlag = false;							//�W�����v�Ŕ����󂵂���
	float jumpPower = 8.0f;								//�W�����v�p���[
	float jumpPowerDelay = 0.2f;						//�W�����v�p���[����
	float gravity = 5.0f;								//�d��
	bool groundFlag = false;							//�n�ʂɐڂ��Ă��邩�ǂ���
	bool oldGroundFlag = false;							//�n�ʂɐڂ��Ă������ǂ���
	bool blockStepOnFlag = false;						//�u���b�N�𓥂�ŉ󂵂����ǂ���

	//�X�s���X�e�[�^�X
	Box spinAttack = {};								//�X�s����
	const float spinScale = 10.0f;						//�X�s���̑傫��
	const int spinCoolTimeMax = 100;					//�X�s���̃N�[���^�C���ő�
	int spinCoolTime = 0;								//�X�s���̃N�[���^�C��
	bool spinFlag = false;								//�X�s����������

	//��
	bool fishFlag = false;								//�����l��������								
	int fishNum = 0;									//���l����

	//�v���C���[���o
	Staging staging;									//���o�N���X
	int dieNowTime = 0;									//���S���o����
	int dieType = DIENULL;								//���S�^�C�v
	const int walkTimeMax = 5;							//�����p�[�e�B�N�����o������
	int walkTime = walkTimeMax;							//�����p�[�e�B�N�����o�����ԍő�

	//�X�e�[�W�J�n���̉��o�t���O
	bool starStaging = false;
	const int startTimeMax = 60;
	int startTime = 0;

	//���S���̏��
	const float fallPos = -30.0f;					//�������̍��W
	//�����S��
	Vec3 fishDiePos = {};
	Vec3 fishDieAngle = {};
	bool isFishDie = false;
	int decLifeTime = 0;

	//FBX�N���X
	PlayerFBX pFbx;										
	//���f�[�^
	int audioTime = 0;									//�����o���Ԋu
	SoundData walkSE = {};								//������
	SoundData fallSE = {};								//�����鉹
	SoundData electSE = {};								//�d�C�̉�
};