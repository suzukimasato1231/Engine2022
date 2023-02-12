#pragma once
#include "_DirectX.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include"Sprite.h"
#include<memory>
extern const int window_width;
extern const int window_height;
/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize();

	void Init();

	void Update();

	void Draw();

	void ShadowDraw();

	void Delete();
private:
	std::unique_ptr<LightGroup>lightGroup;
private://��`
	ObjectData box;
	PSR boxPsr = {};
	int boxGraph;

	//�S�[�����̉��o�n���h�T�C��
	Model* penginModel;
	std::unique_ptr<FBXObject3d> penginHandFbx;

	ObjectData wallObj;
	PSR wallPsr;

	ObjectData floorObj;

	//UI
	SpriteData titleGraph;
	SpriteData titleButtonGraph;
	int buttonTime = 0;
};


