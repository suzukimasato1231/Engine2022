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

	inline bool GetScene() { return nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model> penginModel;
	std::unique_ptr<FBXObject3d> penginHandFbx;

	PSR objectPsr = {};
	ObjectData fishObj;
	ObjectData floorObj;

	//��ꂽ�����U���g
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;

	SpriteData clearGraph;
	SpriteData selectGraph;
	SpriteData nextGraph;
	int nextScene = 0;
	const float nextScaleMax = 1.2f;
	const float nextScaleMin = 0.8f;
	bool nextScaleFlag = false;
	float nextScale = 1.0f;

	//�{�^��
	SpriteData buttonGraph;
	int buttonTime = 0;

	//���f�[�^
	SoundData decisionSE = {};
	SoundData selectSE = {};
};