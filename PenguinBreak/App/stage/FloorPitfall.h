#pragma once
#include"./StegeObject.h"
/// <summary>
/// ��]��
/// </summary>
class FloorPitfall
{
private:
	/// <summary>
	/// �J���Ă��邩���Ă��邩
	/// </summary>
	enum PitfallOpenClose
	{
		PITFALLCLOSE,
		PITFALLOPEN,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FloorPitfall();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~FloorPitfall();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="floorData">���f�[�^</param>
	void Update(Floor* floorData);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="floorData">���f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(Floor* floorData, const bool shadowFlag);
private:
	ObjectData m_pitfallOBJ;						//��OBJ
	int m_pitfallGraph = 0;							//���摜
	const int c_pitfallTime = 70;					//��]����
	const int c_pitfallSpeed = 18;					//��]���x
	const Vec3 c_pitfallScale = { 25.0f,5.0f,25.0f };//	�`��X�P�[��
};

