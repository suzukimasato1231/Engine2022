#include <Object.h>
#include<memory>
#include"FBXObject3d.h"
#include<Audio.h>
/// <summary>
/// �V�[���ړ�
/// </summary>
enum ResultNext
{
	ResultNextStage,
	ResultSelect,
};

/// <summary>
/// ���U���g�V�[��
/// </summary>
class ResultScene
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
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// ���[�v������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageNum">�X�e�[�W</param>
	void Draw(const int stageNum);
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw();

	inline bool GetScene() { return  m_nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData  m_resultOBJ;
	int  m_resultTime = 0;

	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model>  m_penginModel;
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;

	PSR  m_objectPsr = {};
	ObjectData  m_fishObj;
	ObjectData  m_floorObj;

	//��ꂽ�����U���g
	SpriteData  m_uiNumber[10];
	SpriteData  m_uiSlash;
	SpriteData  m_boxGraph;

	SpriteData  m_clearGraph;
	SpriteData  m_selectGraph;
	SpriteData  m_nextGraph;
	int  m_nextScene = 0;
	const float c_nextScaleMax = 1.2f;
	const float c_nextScaleMin = 0.8f;
	bool  m_nextScaleFlag = false;
	float  m_nextScale = 1.0f;

	//�{�^��
	SpriteData  m_buttonGraph;
	int  m_buttonTime = 0;

	//���f�[�^
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
};