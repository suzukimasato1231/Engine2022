#pragma once
#include"Menu.h"
//UI�N���X
class UI
{

public:
	UI();
	~UI();

	void Init();

	void Update(int fishNum, bool& changeScene, int& sceneNum);

	void Draw(const int pLives, const  bool gameoverFlag);

	void Reset();

	bool GetMenuFlag() { return menuFlag; }
private:
	//�Q�[�����UI
	SpriteData boxGraph;

	SpriteData playerIcon;

	SpriteData fishGraph;

	SpriteData uiNumber[10];
	SpriteData uiSlash;

	//���j���[
	Menu menu;
	bool menuFlag = false;

	//���o(�Q�[�����)
	float fishPosPlas = 0.0f;
	const int stagingTimeMax = 20;
	const float stagingScaleMax = 1.5f;
	float stagingScale[4] = { 0.0f,0.0f,0.0f,0.0f };
	int stagingTime[4] = {};
	bool stagingFlag[4] = {};
	//�󂵂����̐�
	int breakNumber = 1, breakRemain = 1;
	//�ő唠�̐�
	int breakNumberMax = 1, breakRemainMax = 1;
	//���̐�
	int fishNumber = 1, fishRemain = 1;
};

