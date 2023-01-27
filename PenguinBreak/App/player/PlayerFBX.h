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
	PlayerFBX();

	~PlayerFBX();
	//FBX�ǂݎ��
	void Load();

	void Update();
	//�`��
	void Draw(Vec3 fbxPos, Vec3 angle, bool shadowFlag);
	//���Z�b�g
	void Reset();
	//�������폜
	void Delete();
	//FBX�𓮂���
	void PlayFBX(int fbxType);
	//�A�j���[�V�������~�߂�
	void StopAnimation();
	//�A�j���[�V�����X�^�[�g
	void StartAnimation();
private:
	int fbxType = NULL;
	int fbxFlag = 1;
	//����FBX
	Model* model1 = nullptr;
	std::unique_ptr<FBXObject3d> fbxObject1;
	//����FBX
	Model* walkModel = nullptr;
	std::unique_ptr<FBXObject3d> walkFbx;
	//��~FBX
	Model* stopModel = nullptr;
	std::unique_ptr<FBXObject3d> stopFbx;
	//���d
	Model* electModel = nullptr;
	std::unique_ptr<FBXObject3d> electFbx;
	//�S�[�����̉��o�o�N�V
	Model* goalJumpModel = nullptr;
	std::unique_ptr<FBXObject3d> goalJumpFbx;
	//�S�[�����̉��o�n���h�T�C��
	Model* goalHandModel = nullptr;
	std::unique_ptr<FBXObject3d> goalHandFbx;
	//�W�����v���̉��o�n���h�T�C��
	Model* jumpModel = nullptr;
	std::unique_ptr<FBXObject3d> jumpFbx;
	const int jumpTimeMax = 30;
	int jumpTime = 0;

	bool menuStopFlag = false;
};

