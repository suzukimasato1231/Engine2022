#include <Sprite.h>
/// <summary>
/// ���j���[�N���X
/// </summary>
class Menu
{
public:
	//�R���X�g���N�^
	Menu();
	//�f�X�R���X�g���N�^
	~Menu();
	//������
	void Init();
	//�X�V
	void Update(bool& menuFlag, bool& changeScene, int& sceneNum);
	//�`��
	void Draw(const bool gameoverFlag);

	void Reset();
private:
	//���j���[�֘A
	SpriteData menuButton;
	SpriteData menuFream;
	SpriteData menuRetry;
	SpriteData menuVolum;
	SpriteData menuStageSelect;
	SpriteData menuFish;
	int menuNum = 0;
	//���j���[�̋���
	bool menuTimeFlag = false;
	float menuScale = 1.0f;
	//�C�[�W���O�i���j���[�j
	const Vec3 c_start = { 1500.0f,300.0f,0.0f };
	const Vec3 c_end = { 950.0f,300.0f,0.0f };
	Vec3 menuPos = { 0.0f,0.0f ,0.0f };
	bool menuEasingFlag = false;
	//�o�Ă���Ƃ�
	const float c_startTimeMax = 20.0f;
	float m_startTime = 0.0f;

	//��
	SpriteData menuAudioFream;
	SpriteData menuAudioVolum;
	SpriteData menuAudioLandmark;
	//���ʒ����t���O
	bool audioFlag = false;
	
	const float volumMax = 0.10f;
	const float volumMin = 0.0f;
	float volum = 0.02f;

};