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

	void ChangeFlag() { isPointFlag = false; }
private:
	ObjectData dropPointOBJ = {};

	int dropPointGraph = 0;

	PSR dropPointPSR = {};

	Vec3 position = {};

	bool isPointFlag = false;

	float groundDistance = 0.0f;
};

