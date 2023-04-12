#pragma once
#include"StegeObject.h"
#include"ParticleManager.h"
#include<memory>
/// <summary>
/// �d�C���
/// </summary>
class Electricity
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Electricity();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~Electricity();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �S�̂̍X�V
	/// </summary>
	void AllUpdate();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="Z">Z���ʒu</param>
	void Update(StageData* stageObj);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(StageData* stageObj, const bool shadowFlag);
	/// <summary>
	/// �p�[�e�B�N���`��
	/// </summary>
	void DrawParicle();
private:
	//�d�C�p�[�e�B�N��
	void AddElect(Vec3 pos, Vec3 scale);
private:
	ObjectData m_electOBJ;			//�d�C���I�u�W�F�N�g
	ObjectData m_electShockOBJ;		//�d�C�I�u�W�F�N�g
	bool m_electFlag = false;		//�d�CON/OFF
	const int c_electTimeMax = 150;	//�d�C�؂�ւ��ő厞�Ԏ���
	int m_electTime = 0;			//�؂�ւ��܂ł̎���
	//�d�C�т�т�
	std::unique_ptr<ParticleManager>m_electParicle = nullptr;
	TextureData m_electParicleGraph = {};

	const Vec2 c_uvScrollSpeed = { 0.0f, 0.002f };	//uv�X�N���[�����x
	Vec2 m_uvScroll = { 0.0f ,0.0f };				//uv�ʒu
};

