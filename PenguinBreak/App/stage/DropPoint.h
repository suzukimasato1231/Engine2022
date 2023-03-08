#pragma once
#include"Object.h"
#include"../stage/StegeObject.h"
/// <summary>
/// �����n�_
/// </summary>
class DropPoint
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DropPoint();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~DropPoint();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	///	�X�V
	/// </summary>
	/// <param name="pPos">�v���C���[���W</param>
	/// <param name="pos">�����W</param>
	/// <param name="angle">�p�x</param>
	/// <param name="scale">�傫��</param>
	void Update(const Vec3 &pPos, const Vec3 &pos, const Vec3 &angle, const Vec3 &scale);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pPos">���W</param>
	void Draw(const Vec3 &pPos);

	void ChangeFlag() { m_isPointFlag = false; }
private:
	ObjectData  m_dropPointOBJ = {};					//����OBJ

	int  m_dropPointGraph = 0;							//�����摜

	PSR  m_dropPointPSR = {};

	Vec3  m_position = {};								//���W

	bool  m_isPointFlag = false;

	float  m_groundDistance = 0.0f;
};

