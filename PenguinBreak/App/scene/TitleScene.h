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
	ObjectData  m_box;								//��OBJ
	PSR  m_boxPsr = {};							//��PSR�ۑ�
	int  m_boxGraph;								//���摜

	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model> m_penginModel;			//�y���M�����f��
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;	//�y���M��FBX

	ObjectData  m_wallObj;							//��OBJ
	PSR  m_wallPsr;								//�ePSR�ۑ�
		
	ObjectData  m_floorObj;						//��OBJ

	//UI
	SpriteData  m_titleGraph;						//�^�C�g���摜
	SpriteData  m_titleButtonGraph;				//�{�^���摜
	int  m_buttonTime = 0;							//�{�^���_��
};


