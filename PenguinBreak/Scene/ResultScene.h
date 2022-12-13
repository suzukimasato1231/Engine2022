#include <Object.h>
#include<memory>
#include"FBXObject3d.h"

enum ResultNext
{
	ResultNextStage,
	ResultSelect,
};


class ResultScene
{
private:

public:
	ResultScene();

	~ResultScene();

	void Initialize();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(const int stageNum);

	void Delete();

	void ShadowDraw();

	bool GetScene() { return nextScene; }
private:
	std::unique_ptr<LightGroup> lightGroup;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	//�S�[�����̉��o�n���h�T�C��
	Model* penginModel = nullptr;
	std::unique_ptr<FBXObject3d> penginHandFbx[2];

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
};