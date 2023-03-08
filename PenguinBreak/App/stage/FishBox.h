#pragma once
#include"Object.h"
#include<vector>
/// <summary>
/// ���N���X
/// </summary>
class FishBox
{
private:
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
	//����������
	void Init();
	//�X�V����
	void Update(const Vec3 &pPos);
	//�`�揈��
	void Draw();
	//�쐬����
	void Create(const Vec3 &pos);

	void Delete();
private:
	ObjectData fishOBJ;
	std::vector<FishData*>fishData;
	//�傫��
	const Vec3 scale = { 1.8f,1.8f,1.8f };
	//UI�̋��̈ʒu
	const Vec3 fishGoalPos = { -70.0f,50.0f,10.0f };
	//�ړ����鎞��
	const float time = 50.0f;
};

