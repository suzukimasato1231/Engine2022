#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"

class Enemy;

class Player :public Singleton<Player>
{
public:
	friend Singleton<Player>;
public:
	Player();//�R���X�g���N�^

	~Player();//�ł��R���X�g���N�^

	void Init();//������

	void Update(class Enemy *enemy);//�X�V

	void Draw();//�`��

	void SetPosition(Vec3 position);
	/// <summary>
	/// true�ɂ���
	/// </summary>
	void GroundFlag();

	void Reset();
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
public://�擾�n
	//���W
	Vec3 GetPosition() { return position; }

	Vec3 GetOldPosition() { return oldPosition; }

	Vec3 GetPSize() { return pScale; }

	Sphere GetSphere() { return pSphere; }

	Box GetBox() { return pBox; }

	Vec3 GetVec() { return vec; }

	float GetJumpPower() { return jumpPower; }
private:
	ObjectData playerObject;			//�v���C���[�I�u�W�F�N�g
	Vec3 position{ 10.0f,20.0f,0.0f };	//���W
	Vec3 oldPosition{};					//1�O�̍��W
	Vec3 speed{ 2.0f,2.0f,2.0f };		//�v���C���[�X�s�[�h
	Vec3 scale{ 4.0f,4.0f,4.0f };		//�傫��
	Vec3 angle{ 0.0f,0.0f,0.0f };		//�p�x
	Vec4 color{ 1.0f,1.0f,1.0f,1.0f };	//�F
	Vec3 pScale = { 5.0f,7.0f,5.0f };	//�v���C���[�傫��
	Sphere pSphere;						//�v���C���[�̋�
	Box pBox;							//�v���C���[�̔�
	int HP = 10;						//�v���C���[HP


	Vec3 vec = {};						

	//�W�����v
	const float jumpPowerMax = 8.0f;
	float jumpPower = 8.0f;//�W�����v�p���[
	float jumpPowerDelay = 0.2f;
	float gravity = 5.0f;//�d��
	bool groundFlag = false;//�n�ʂɐڂ��Ă��邩�ǂ���
};