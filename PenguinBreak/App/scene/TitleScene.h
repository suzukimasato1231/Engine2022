#pragma once
#include "DirectXBase.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include"Sprite.h"
#include<memory>
#include"BaseScene.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene :public BaseScene
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

	void Init(int stageNum)override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(int& stageNum, int m_breakBox[])override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const int stageNum)override;
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw()override;
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw()override;
	void Finalize()override;
private:
	std::unique_ptr<LightGroup>lightGroup;
private://��`
	ObjectData  m_box;							//��OBJ
	PSR  m_boxPsr = {};							//��PSR�ۑ�
	TextureData  m_boxGraph;					//���摜

	SoundData  m_buttonSE = {};                 //�{�^��SE

	//�S�[�����̉��o�n���h�T�C��
	std::unique_ptr<Model> m_penginModel;		  //�y���M�����f��
	std::unique_ptr<FBXObject3d>  m_penginHandFbx;//�y���M��FBX

	ObjectData  m_wallObj;						//��OBJ
	PSR  m_wallPsr;								//�ePSR�ۑ�

	ObjectData  m_floorObj;						//��OBJ

	//UI
	SpriteData  m_titleGraph;					//�^�C�g���摜
	SpriteData  m_titleButtonGraph;				//�{�^���摜
	int  m_buttonTime = 0;						//�{�^���_��
};


