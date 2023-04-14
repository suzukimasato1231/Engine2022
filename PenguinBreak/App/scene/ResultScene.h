#include <Object.h>
#include<memory>
#include"FBXObject3d.h"
#include<Audio.h>
#include"BaseScene.h"
#include<Sprite.h>
/// <summary>
/// �V�[���ړ�
/// </summary>
enum class ResultNext
{
	ResultNextStage,
	ResultSelect,
};

/// <summary>
/// ���U���g�V�[��
/// </summary>
class ResultScene:public BaseScene
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ResultScene();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~ResultScene();
	/// <summary>
	/// ���[�v������
	/// </summary>
	void Init(int stageNum)override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(int& stageNum, int m_breakBox[])override;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageNum">�X�e�[�W</param>
	void Draw(const int stageNum)override;
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw()override;
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw()override;

	void Finalize()override;
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData  m_resultOBJ;
	const int c_resultTimeMax = 500;//���U���g���o��܂ł̍ő厞��
	int  m_resultTime = 0;          //���U���g���o��܂ł̎���
	const int c_buttonMax = 60;     //�_�ł̊Ԋu
	const int c_clearTimeMax = 30;  //�N���A��ʂ��o������
	const int c_numberTime = 60;    //�N���A���Ă��琔�����o������
	const int stageMax = 3;         //�ő�X�e�[�W��
	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model>  m_penginModel;
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;
	const Vec3 fbxScale = { 0.015f,0.015f,0.015f };//fbx�̑傫��

	PSR  m_objectPsr = {};
	ObjectData  m_fishObj;
	ObjectData  m_floorObj;

	//��ꂽ�����U���g
	SpriteData  m_uiNumber[10]={};
	SpriteData  m_uiSlash={};
	SpriteData  m_boxGraph={};

	SpriteData  m_clearGraph;
	SpriteData  m_selectGraph;
	SpriteData  m_nextGraph;
	//int  m_nextScene = 0;
	const float c_selectScaleSpeed = 0.02f;//�傫�����ς��X�s�[�h
	const float c_nextScaleMax = 1.2f;     //�ő�̑傫��
	const float c_nextScaleMin = 0.8f;     //�ŏ��̑傫��
	bool  m_nextScaleFlag = false;
	float  m_nextScale = 1.0f;


	const float numberScale = 128.0f;     //�����̑傫��

	//�{�^��
	SpriteData  m_buttonGraph;
	int  m_buttonTime = 0;

	//���f�[�^
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
	SoundData  m_buttonSE = {};                 //�{�^��SE
};