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
enum class DieType
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
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
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
	void ActivateGround() { m_groundFlag = true; }
	/// <summary>
	/// �l���Z�b�g
	/// </summary>
	void Reset();
	/// <summary>
	///�@�����W�����v�ŉ󂵂���
	/// </summary>
	void ActivateBlockStepOn() { m_blockStepOnFlag = true; }
	/// <summary>
	/// �W�����v�͂��[���ɂ���
	/// </summary>
	void JumpPoweZero() { m_jumpPower = 0; }
	/// <summary>
	/// 2D false 3D true�@
	/// </summary>
	/// <param name="moveFlag">2D��3D�̃t���O</param>
	void SetMoveFlag(bool moveFlag) { m_moveFlag = moveFlag; }
	/// <summary>
	/// �W�����v���𓥂񂾂�
	/// </summary>
	void ActivateJumpBox() { m_jumpBoxFlag = true; }
	/// <summary>
	/// �����󂵂���
	/// </summary>
	void ActivateChangeBreak() { m_changeBreakFlag = true; }

	void DieType(int type) { if (m_dieType != static_cast<int>(DieType::DIENOW)) { m_dieType = type; } }

	void FishDie(const Vec3& pos, const Vec3& angle) { m_fishDiePos = pos, m_fishDieAngle, angle; }
	//�S�[�����̉��o
	void GoalStaging(int fbxType);

	void GetClearFlag(bool clearFlag) { m_clearFlag = clearFlag; }

	int GetDecLifeFlag() { return m_decLifeTime; }

	void StopAnimation();
private:
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
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="pos">�v���C���[�ʒu</param>
	/// <returns></returns>
	bool OutofFallDown(const Vec3& pos);
public://�擾�n
	inline Vec3 GetPosition() { return m_position; }

	inline Vec3 GetOldPosition() { return m_oldPosition; }

	inline Vec3 GetPSize() { return m_pScale; }

	inline Box GetBox() { return m_pBox; }

	inline Vec3 GetVec() { return m_vec; }

	inline float GetJumpPower() { return m_jumpPower; }

	inline bool GetGroundFlag() { return m_groundFlag; }

	inline bool GetOldGroundFlag() { return m_oldGroundFlag; }
	
	inline int GetRemanLives() { return m_remainLives; }

	inline int GetFishNum() { return m_fishNum; }

	inline bool GetGameoverFlag() { return m_gameoverFlag; }

	inline bool GetIsFishDie() { return m_isFishDie; }

	inline Box GetSpinBox() { return m_spinAttack; }

	inline bool GetSpinFlag() { return m_spinFlag; }
private:
	//�Q�[���t���O
	bool m_moveFlag = false;								//2D false 3D true
	bool m_gameoverFlag = false;							//�Q�[���I�[�o�[���ǂ���
	bool m_clearFlag = false;								//�N���A�������ǂ���
	//�v���C���[�X�e�[�^�X
	ObjectData m_playerObject;							//�v���C���[�I�u�W�F�N�g
	PSR m_psr = {};										//�v���C���[�̈ʒu���W�傫���ۑ��p
	Vec3 m_position = { 94.0f,14.0f,80.0f };				//���W
	const Vec3 c_firstPosition = { 90.0f,25.0f,80.0f };	//�����ʒu
	Vec3 m_oldPosition = {};								//1�O�̍��W
	const Vec3 c_speed = { 2.0f,2.0f,2.0f };				//����X�s�[�h
	const Vec3 c_walkSpeed = { 1.0f,1.0f,1.0f };			//�����X�s�[�h
	Vec3 m_angle = { -30.0f,180.0f,0.0f };				//�p�x
	const Vec3 c_firstAngle = { -30.0f,180.0f,0.0f };		//�ŏ��̊p�x
	Vec3 m_pScale = { 12.0f,5.0f,12.0f };					//�v���C���[�̑傫��
	Box m_pBox;											//�v���C���[BOX
	Vec3 m_vec = {};
	bool m_changeBreakFlag = false;

	const int c_remainLivesMax = 3;						//�P�X�e�[�W�̎c�@��
	int m_remainLives = 3;								//�c�@

	//�W�����v
	const float c_jumpPowerMax = 8.0f;					//�W�����v�p���[
	const float c_jumpBoxPowerMax = 9.0f;					//�W�����v��̃W�����v�p���[
	bool m_jumpBoxFlag = false;							//�W�����v�Ŕ����󂵂���
	float m_jumpPower = 8.0f;								//�W�����v�p���[
	float m_jumpPowerDelay = 0.2f;						//�W�����v�p���[����
	float m_gravity = 5.0f;								//�d��
	bool m_groundFlag = false;							//�n�ʂɐڂ��Ă��邩�ǂ���
	bool m_oldGroundFlag = false;							//�n�ʂɐڂ��Ă������ǂ���
	bool m_blockStepOnFlag = false;						//�u���b�N�𓥂�ŉ󂵂����ǂ���

	//�X�s���X�e�[�^�X
	Box m_spinAttack = {};								//�X�s����
	const float c_spinScale = 10.0f;						//�X�s���̑傫��
	const int c_spinCoolTimeMax = 100;					//�X�s���̃N�[���^�C���ő�
	int m_spinCoolTime = 0;								//�X�s���̃N�[���^�C��
	bool m_spinFlag = false;								//�X�s����������

	//��
	bool m_fishFlag = false;								//�����l��������								
	int m_fishNum = 0;									//���l����
	const int c_fishMax = 100;							//�ő�l����
	const int c_fishPlas = 5;								//���̊l����

	//�v���C���[���o
	Staging m_staging;									//���o�N���X
	int m_dieNowTime = 0;									//���S���o����
	int m_dieType = static_cast<int>(DieType::DIENULL);								//���S�^�C�v
	const int c_walkTimeMax = 5;							//�����p�[�e�B�N�����o������
	int m_walkTime = c_walkTimeMax;							//�����p�[�e�B�N�����o�����ԍő�

	//�X�e�[�W�J�n���̉��o�t���O
	bool m_starStaging = false;
	const int c_startTimeMax = 60;
	int m_startTime = 0;

	//���S���̏��
	const float c_fallPos = -30.0f;						//�������̍��W
	//�����S��
	Vec3 m_fishDiePos = {};
	Vec3 m_fishDieAngle = {};
	bool m_isFishDie = false;
	int m_decLifeTime = 0;

	//FBX�N���X
	PlayerFBX m_pFbx;
	//���f�[�^
	int m_audioTime = 0;									//�����o���Ԋu
	SoundData m_walkSE = {};								//������
	SoundData m_fallSE = {};								//�����鉹
	SoundData m_electSE = {};								//�d�C�̉�
};