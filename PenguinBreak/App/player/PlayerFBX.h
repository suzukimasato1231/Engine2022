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
	int fbxType = NULL;
	int fbxFlag = 1;
	//����FBX
	std::unique_ptr<Model> fbxModel = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject1;
	//����FBX
	std::unique_ptr<Model> walkModel = nullptr;
	std::unique_ptr<FBXObject3d> walkFbx;
	//��~FBX
	std::unique_ptr<Model> stopModel = nullptr;
	std::unique_ptr<FBXObject3d> stopFbx;
	//�X�s��FBX
	std::unique_ptr<Model> spinModel = nullptr;
	std::unique_ptr<FBXObject3d> spinFbx;
	const int spinTimeMax = 30;
	int spinTime = 0;
	//���d
	std::unique_ptr<Model> electModel = nullptr;
	std::unique_ptr<FBXObject3d> electFbx;
	//�S�[�����̉��o�o�N�V
	std::unique_ptr<Model> goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d> goalJumpFbx;
	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model> goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d> goalHandFbx;
	//�W�����v���̉��o�n���h�T�C��
	std::unique_ptr<Model> jumpModel = nullptr;
	std::unique_ptr<FBXObject3d> jumpFbx;
	const int jumpTimeMax = 30;
	int jumpTime = 0;

	bool menuStopFlag = false;
};

