#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/// <summary>
/// FPS�Ǘ��p�N���X�A��������Ӗ����Ȃ��̂ŃV���O���g���p�^�[���̗p
/// </summary>
class FPS final
{
private:
	const float MIN_FREAM_TIME = 1.0f / 60.0f;
	float frameTime = 0;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	// fps���擾����Ȃ�0�ŏ��������Ȃ��ƃS�~���������ă}�C�i�X����n�܂����肷��(�����m��Ȃ�)
	float fps = 0;

	//�R���X�g���N�^�A�f�X�g���N�^���B��
	FPS() {};
	~FPS() {};

public:

	//������s
	void Start();

	//FPS�����̎��s
	void run();

	//�C���X�^���X�擾
	static FPS* Get();

	//�R�s�[�R���X�g���N�^�A������Z�q������
	FPS(const FPS& obj) = delete;
	FPS& operator=(const FPS& obj) = delete;

};
