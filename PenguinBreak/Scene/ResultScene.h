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

	~ResultScene();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	//���[�v������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(const int stageNum);
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
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
	Model* penginModel = nullptr;
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