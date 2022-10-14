#pragma once
#include"Object.h"
#include<vector>
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

	FishBox();

	~FishBox();
	//����������
	void Init();
	//�X�V����
	void Update(Vec3 pPos);
	//�`�揈��
	void Draw();
	//�쐬����
	void Create(Vec3 pos);

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

