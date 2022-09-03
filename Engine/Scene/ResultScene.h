#include"Singleton.h"
#include <Object.h>

class ResultScene 
{
private:

public:
	void Initialize();

	void Init();

	void Update();

	void Draw();
private:
	ObjectData resultOBJ;

	int resultTime = 0;


	//��ꂽ�����U���g
	SpriteData uiNumber[10];
	SpriteData uiSlash;
	SpriteData boxGraph;


	//�{�^��
	SpriteData buttonGraph;
	int buttonTime = 0;
};