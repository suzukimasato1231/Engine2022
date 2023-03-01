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
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleScene();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~TitleScene();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw();
private:
	std::unique_ptr<LightGroup>lightGroup;
private://��`
	ObjectData box;								//��OBJ
	PSR boxPsr = {};							//��PSR�ۑ�
	int boxGraph;								//���摜

	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model>penginModel;			//�y���M�����f��
	std::unique_ptr<FBXObject3d> penginHandFbx;	//�y���M��FBX

	ObjectData wallObj;							//��OBJ
	PSR wallPsr;								//�ePSR�ۑ�
		
	ObjectData floorObj;						//��OBJ

	//UI
	SpriteData titleGraph;						//�^�C�g���摜
	SpriteData titleButtonGraph;				//�{�^���摜
	int buttonTime = 0;							//�{�^���_��
};


