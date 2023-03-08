#pragma once
#include"./StegeObject.h"
/// <summary>
/// ��]��
/// </summary>
class FloorPitfall
{
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
	ObjectData m_pitfallOBJ;
	int m_pitfallGraph = 0;
	const int c_pitfallTime = 70;
};

