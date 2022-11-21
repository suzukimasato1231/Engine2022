#include"Singleton.h"
#include <Object.h>
#include<memory>
#include"FBXObject3d.h"
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
	void Draw();

	void Delete();

	void ShadowDraw();
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

	//�{�^��
	SpriteData buttonGraph;
	int buttonTime = 0;
};