#pragma once
#include"Object.h"
#include<vector>
/// <summary>
/// ���N���X
/// </summary>
class FishBox
{
private:
	/// <summary>
	/// ���f�[�^
	/// </summary>
	struct FishData
	{
		Vec3 position = {};
		Vec3 startPosition = {};
		float fishTime = 0.0f;
		bool endFlag = false;
		PSR psr = {};
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FishBox();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~FishBox();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="pPos">�v���C���[�ʒu</param>
	void Update(const Vec3 &pPos);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �쐬����
	/// </summary>
	/// <param name="pos">�쐬�ʒu</param>
	void Create(const Vec3 &pos);
	/// <summary>
	/// �f�[�^����
	/// </summary>
	void Delete();
private:
	ObjectData m_fishOBJ;
	std::vector<FishData*>fishData;
	//�傫��
	const Vec3 c_scale = { 1.8f,1.8f,1.8f };
	//UI�̋��̈ʒu
	const Vec3 c_fishGoalPos = { -70.0f,50.0f,10.0f };
	//�ړ����鎞��
	const float c_time = 50.0f;
};

