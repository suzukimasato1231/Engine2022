#include"Singleton.h"
#include <Object.h>

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

	void ShadowDraw();
private:
	LightGroup* lightGroup = nullptr;
private:
	ObjectData resultOBJ;
	int resultTime = 0;

	ObjectData penginObj;
	PSR objectPsr = {};
	ObjectData fishObj;
	ObjectData floorObj;

	//��ꂽ�����U���g
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;

	//�{�^��
	SpriteData buttonGraph;
	int buttonTime = 0;
};