#pragma once
#include"FBXObject3d.h"
#include<memory>
/// <summary>
/// �v���C���[FBX�̏��
/// </summary>
enum PlayerFBXType
{
	FbxNone,
	FbxWalk,
	FbxElectDie,
	FbxGoalJump,
	FbxGoalHand,
	FbxJump,
	FbxWalking,
	FbxSpin,
	FBXMAX,
};
/// <summary>
/// �v���C���[��FBX�N���X
/// </summary>
class PlayerFBX
{
private:
	enum LoopFbx
	{
		FbxLoopStop,
		FbxLoopWalk,
		FbxLoopRun,
		FbxLoopMax,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerFBX();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~PlayerFBX();
	/// <summary>
	/// �ǂݎ��
	/// </summary>
	void Load();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(const Vec3& fbxPos, const Vec3& angle);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="fbxPos">���W</param>
	/// <param name="angle">�p�x</param>
	/// <param name="shadowFlag">�V���h�E�t���O</param>
	void Draw(bool shadowFlag);
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();
	/// <summary>
	/// FBX�𓮂���
	/// </summary>
	/// <param name="fbxType">fbx�^�C�v</param>
	void PlayFBX(int fbxType);
	/// <summary>
	/// �A�j���[�V�������~�߂�
	/// </summary>
	void StopAnimation();
	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void StartAnimation();
private:
	int m_fbxType = NULL;
	int  m_fbxFlag = 1;
	//����FBX
	std::unique_ptr<Model>  m_fbxModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_fbxObject1;
	//����FBX
	std::unique_ptr<Model>  m_walkModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_walkFbx;
	//��~FBX
	std::unique_ptr<Model> m_stopModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_stopFbx;
	//�X�s��FBX
	std::unique_ptr<Model>  m_spinModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_spinFbx;
	const int c_spinTimeMax = 30;
	int  m_spinTime = 0;
	//���d
	std::unique_ptr<Model>  m_electModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_electFbx;
	//�S�[�����̉��o�o�N�V
	std::unique_ptr<Model>  m_goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_goalJumpFbx;
	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model>  m_goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_goalHandFbx;
	//�W�����v���̉��o�n���h�T�C��
	std::unique_ptr<Model>  m_jumpModel = nullptr;
	std::unique_ptr<FBXObject3d>  m_jumpFbx;
	const int  m_jumpTimeMax = 30;
	int  m_jumpTime = 0;

	bool  m_menuStopFlag = false;
};

